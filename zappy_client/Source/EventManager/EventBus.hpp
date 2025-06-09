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
class EventBus {
    public:
        template<typename EventType>
        using Handler = std::function<void(const EventType &)>;

        EventBus() = default;
        ~EventBus() = default;

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
        using EventHandler = std::function<void(const IEvent &)>;
        std::unordered_map<std::type_index, std::vector<EventHandler>> _subscribers;
};
}
}
