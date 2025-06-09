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
                        "EventType must inehrite from IEvent");
            auto typeId = std::type_index(typeid(EventType));
            auto wrapper = [handler = std::move(handler)](const IEvent &evt) {
                handler(static_cast<const EventType &>(evt));
            };
            _subscribers[typeId].push_back(wrapper);
        }

        /**
         * @brief Publishes an event to all subscribed handlers
         * 
         * @tparam EventType The type of event being published
         * @param event The event object to publish
         */
        template<typename EventType>
        void publish(const EventType &event) const
        {
            auto it = _subscribers.find(std::type_index(typeid(EventType)));
            if (it != _subscribers.end()) {
                for (const auto &handler : it->second) {
                    handler(event);
                }
            }
        }
    private:
        /**
         * @brief Type alias for internal event handler functions
         * Handles events through the common IEvent base interface
         */
        using EventHandler = std::function<void(const IEvent &)>;
        
        /**
         * @brief Map of event type to vector of handlers
         * Each event type (identified by type_index) has a vector of handlers that process it
         */
        std::unordered_map<std::type_index, std::vector<EventHandler>> _subscribers;
};
} // namespace EventManager
} // namespace GUI
