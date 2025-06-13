/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** EventBus
*/

#pragma once

#include <unordered_map>
#include <typeindex>
#include <functional>
#include <queue>
#include <mutex>
#include <memory>
#include "EventManager/IEvent.hpp"

namespace GUI {
namespace EventManager {

/**
 * @class EventBus
 * @brief Central event bus for publishing and subscribing to game events
 *
 * The EventBus provides a publish-subscribe mechanism for game components
 * to communicate without direct dependencies. Components can subscribe to
 * specific event types and receive notifications when those events are published.
 */
class EventBus {
    public:
        /**
         * @brief Type alias for event handler functions
         * @tparam EventType The specific event type this handler processes
         */
        template<typename EventType>
        using Handler = std::function<void(const EventType &)>;

        /**
         * @brief Default constructor
         */
        EventBus() = default;

        /**
         * @brief Default destructor
         */
        ~EventBus() = default;

        /**
         * @brief Subscribes a handler function to a specific event type
         * 
         * @tparam EventType The type of event to subscribe to (must inherit from IEvent)
         * @param handler Function to call when the event is published
         */
        template<typename EventType>
        void subscribe(Handler<EventType> handler)
        {
            static_assert(std::is_base_of<IEvent, EventType>::value,
                          "EventType must inherit from IEvent");
            auto typeId = std::type_index(typeid(EventType));
            auto wrapper = [handler = std::move(handler)](const IEvent &evt) {
                handler(static_cast<const EventType &>(evt));
            };
            _subscribers[typeId].push_back(wrapper);
        }

        /**
         * @brief Publishes an event asynchronously to be processed later in the main thread
         * 
         * @tparam EventType The type of event being published
         * @param event The event object to queue
         */
        template<typename EventType>
        void publish(const EventType &event)
        {
            static_assert(std::is_base_of<IEvent, EventType>::value,
                          "EventType must inherit from IEvent");
            std::lock_guard<std::mutex> lock(_queueMutex);
            _pendingEvents.push(std::make_shared<EventType>(event));
        }

        /**
         * @brief Processes all pending events by dispatching them to their subscribed handlers
         * 
         * This should be called from the main thread (e.g., once per frame).
         */
        void processEvents()
        {
            std::queue<std::shared_ptr<IEvent>> eventsToProcess;
            {
                std::lock_guard<std::mutex> lock(_queueMutex);
                std::swap(eventsToProcess, _pendingEvents);
            }
            while (!eventsToProcess.empty()) {
                const std::shared_ptr<IEvent> &event = eventsToProcess.front();
                auto it = _subscribers.find(std::type_index(typeid(*event)));
                if (it != _subscribers.end()) {
                    for (const auto &handler : it->second) {
                        handler(*event);
                    }
                }
                eventsToProcess.pop();
            }
        }

    private:
        using EventHandler = std::function<void(const IEvent &)>;
        std::unordered_map<std::type_index, std::vector<EventHandler>> _subscribers;

        mutable std::mutex _queueMutex;
        std::queue<std::shared_ptr<IEvent>> _pendingEvents;
};
} // namespace EventManager
} // namespace GUI
