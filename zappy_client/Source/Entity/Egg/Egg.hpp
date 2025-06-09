/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Egg
*/

#pragma once

#include "Entity/AEntity.hpp"
#include "GameState/Types/GameTypes.hpp"

namespace GUI {
/**
 * @class Egg
 * @brief Represents an egg entity in the game world
 * 
 * The Egg class extends the abstract AEntity base class to implement
 * egg-specific functionality. It tracks the team association and hatching
 * state of eggs in the game world.
 */
class Egg : public AEntity {
    public:
        /**
         * @brief Constructs an Egg object
         * @param id Unique identifier for the egg
         * @param position Position coordinates of the egg in the game world
         * @param teamName The team name this egg belongs to
         * @param orientation Initial orientation of the egg (defaults to NORTH)
         */
        Egg(uint32_t id, Types::EggId eID, Types::Position position, std::string &teamName,
            Types::Orientation orientation = Types::Orientation::NORTH);
        
        /**
         * @brief Virtual destructor for the Egg class
         */
        ~Egg() = default;

        /**
         * @brief Set the hatched state of the egg
         * @param hatched True if the egg has hatched, false otherwise
         */
        void setHatched(bool hatched);
        
        /**
         * @brief Check if the egg has hatched
         * @return True if the egg has hatched, false otherwise
         */
        bool isHatched() const;
        
    protected:
        std::string m_teamName; ///< The team name this egg belongs to
        Types::EggId m_eggId;   ///< Unique identifier for the egg
        bool m_hatched;         ///< Flag indicating if the egg has hatched
};
}
