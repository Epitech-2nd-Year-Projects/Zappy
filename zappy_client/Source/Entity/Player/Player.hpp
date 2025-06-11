/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Player
*/

#pragma once

#include "Entity/AEntity.hpp"

namespace GUI {
/**
 * @class Player
 * @brief Represents a player entity in the game world
 * 
 * The Player class extends the abstract AEntity base class to implement
 * player-specific functionality. It manages player state including inventory,
 * team membership, level progression, and life status.
 */
class Player : public AEntity {
    public:
        /**
         * @brief Constructs a Player object
         * @param id Unique identifier for the player
         * @param position Shared pointer to the player's position coordinates
         * @param level Initial player level
         * @param teamName The team name this player belongs to
         * @param orientation Initial orientation of the player (defaults to NORTH)
         */
        Player(uint32_t id, Types::PlayerId pId, Types::Position position,
                uint32_t level, const std::string &teamName, Types::Orientation orientation = Types::Orientation::NORTH);

        /**
         * @brief Virtual destructor for the Player class
         */
        ~Player();

        /**
         * @brief Get the player's current inventory
         * @return A ResourceArray containing all resources in the player's inventory
         */
        Types::ResourceArray getInventory() const;
        
        /**
         * @brief Get the player's team name
         * @return The name of the team the player belongs to
         */
        std::string getTeamName() const;
        
        /**
         * @brief Get the player's current level
         * @return The player's level as an unsigned integer
         */
        uint32_t getLevel() const;
        
        /**
         * @brief Get the player's current life points
         * @return The player's life points as an unsigned integer
         */
        uint32_t getLife() const;

        /**
         * @brief Get the player's unique id
         * @return The player's unique id as an unsigned integer
         */
        Types::PlayerId getPlayerId() const;

        /**
         * @brief Check if the player is alive
         * @return true if the player is alive, false otherwise
         */
        bool isAlive() const;

        /**
         * @brief Set the player's inventory contents
         * @param inventory A ResourceArray containing the new inventory state
         */
        void setInventory(const Types::ResourceArray &inventory);
        
        /**
         * @brief Set the player's team name
         * @param teamId The new team name for the player
         */
        void setTeamName(std::string &teamId);
        
        /**
         * @brief Set the player's level
         * @param level The new level value
         */
        void setLevel(uint32_t level);
        
        /**
         * @brief Set the player's life points
         * @param life The new life points value
         */
        void setLife(uint32_t life);
        
        /**
         * @brief Set the player's alive status
         * @param alive true to set the player as alive, false to set as dead
         */
        void setAlive(bool alive);

        /**
         * @brief Remove a specified amount of a resource from the player's inventory
         * @param resourceType The type of resource to remove
         * @param amount The quantity to remove (defaults to 1)
         */
        void removeResource(Types::ResourceType resourceType, std::size_t amount = 1);
        
        /**
         * @brief Add a specified amount of a resource to the player's inventory
         * @param resourceType The type of resource to add
         * @param amount The quantity to add (defaults to 1)
         */
        void addResource(Types::ResourceType resourceType, std::size_t amount = 1);
        
        /**
         * @brief Increase the player's level by one
         */
        void lvlUp();
    protected:
        Types::ResourceArray m_inventory;  ///< The player's resource inventory
        std::string m_teamName;           ///< The team name the player belongs to
        uint32_t m_level;                 ///< The player's current level
        Types::PlayerId m_playerId;       ///< Unique identifier for the player
        uint32_t m_life = 126;            ///< The player's life points, starting at 126
        bool Alive = true;                ///< The player's alive status, initially true
};
}
