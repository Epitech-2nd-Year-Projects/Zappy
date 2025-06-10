/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** IEvent
*/

#pragma once

namespace GUI {
namespace EventManager {

/**
 * @class IEvent
 * @brief Base interface for all event types in the event system
 *
 * The IEvent class serves as the common base for all event types that can be
 * published through the EventBus. Specific event types should inherit from this
 * interface and add their own data members to carry event-specific information.
 * 
 * This base interface enables the EventBus to store and process different event
 * types through a common interface, while allowing type-safe subscription and
 * publishing through templates.
 * 
 * @see EventBus
 */
class IEvent {
    public:
        /**
         * @brief Virtual destructor for the IEvent interface
         * 
         * Ensures proper cleanup of derived event classes when
         * they are destroyed through a pointer to this base interface.
         */
        virtual ~IEvent() = default;
};
} // namespace EventManager
} // namespace GUI
