/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** AEntity
*/

#pragma once

#include <memory>
#include "Entity/IEntity.hpp"
#include "Raylib/Graphics/Animation.hpp"
#include "GameState/Types/GameTypes.hpp"

namespace GUI {
/**
 * @class AEntity
 * @brief Abstract base class for all game entities
 * 
 * The AEntity class provides a common implementation for the IEntity interface.
 * It serves as the base for various entity types in the game world, providing
 * core functionality for positioning and orientation.
 * 
 * @see IEntity
 * @see Player
 * @see MapTile
 * @see Egg
 */
class AEntity : public IEntity {
    public:
        /**
         * @brief Constructs an AEntity object
         * @param id Unique identifier for the entity
         * @param position Position coordinates of the entity in the game world
         * @param orientation Initial orientation of the entity (defaults to NORTH)
         */
        AEntity(uint32_t id, Types::Position position,
                Types::Orientation orientation = Types::Orientation::NORTH);
        
        /**
         * @brief Virtual destructor for the AEntity class
         */
        ~AEntity() = default;

        /**
         * @brief Set the entity's position in the game world
         * @param position New position coordinates
         */
        void setPosition(Types::Position position) override;
        
        /**
         * @brief Set the entity's orientation in the game world
         * @param orientation New orientation direction
         */
        void setOrientation(Types::Orientation orientation) override;
        
    protected:
        uint32_t m_id;              ///< Unique identifier for the entity
        Types::Position m_position; ///< Current position in the game world
        Types::Orientation m_orientation; ///< Current orientation direction
};
}
