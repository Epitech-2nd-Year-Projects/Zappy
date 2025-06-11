/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Entities
*/

#pragma once

#include "GameState/Types/GameTypes.hpp"

namespace GUI {
/**
 * @class IEntity
 * @brief Interface for all entities in the game world
 * 
 * The IEntity interface defines the common operations that all game entities
 * must implement. This includes functionality for positioning, orientation,
 * and rendering entities in the game world.
 */
class IEntity {
    public:
        /**
         * @brief Virtual destructor for the IEntity interface
         */
        virtual ~IEntity() = default;

        /**
         * @brief Set the entity's position in the game world
         * @param position New position coordinates
         */
        virtual void setPosition(Types::Position position) = 0;
        
        /**
         * @brief Set the entity's orientation in the game world
         * @param orientation New orientation direction
         */
        virtual void setOrientation(Types::Orientation orientation) = 0;
};
}
