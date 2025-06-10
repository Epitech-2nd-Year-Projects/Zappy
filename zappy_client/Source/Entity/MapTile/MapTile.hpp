/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Island
*/

#pragma once

#include <map>
#include "Entity/AEntity.hpp"
#include "Entity/Player/Player.hpp"
#include "GameState/Types/GameTypes.hpp"

namespace GUI {
/**
 * @class MapTile
 * @brief Represents a tile on the game map
 * 
 * The MapTile class extends the abstract AEntity base class to implement
 * tile-specific functionality. It manages resources present on the tile
 * and keeps track of players currently positioned on this tile.
 */
class MapTile : public AEntity{
    public:
        /**
         * @brief Constructs a MapTile object
         * @param id Unique identifier for the tile
         * @param position Shared pointer to the tile's position coordinates
         * @param orientation Initial orientation of the tile (defaults to NORTH)
         */
        MapTile(uint32_t id, Types::Position position,
                Types::Orientation orientation = Types::Orientation::NORTH);
        
        /**
         * @brief Destructor for the MapTile class
         */
        ~MapTile();

        /**
         * @brief Get the resources present on this tile
         * @return A ResourceArray containing all resources on the tile
         */
        Types::ResourceArray getResources() const;
        
        /**
         * @brief Get the number of players currently on this tile
         * @return The count of players as a size_t
         */
        std::size_t getNbPlayers() const;

        /**
         * @brief Add a player to this tile
         * @param playerId The unique identifier of the player
         * @param player Shared pointer to the Player object
         */
        void addPlayer(uint32_t playerId, std::shared_ptr<Player> player);
        
        /**
         * @brief Add resources to this tile
         * @param resourceType The type of resource to add
         * @param amount The quantity to add (defaults to 1)
         */
        void addResource(Types::ResourceType resourceType, std::size_t amount = 1);

        /**
         * @brief Add resources to this tile
         * @param resourceArray An array with all ressources of this tile
         */
        void addResource(Types::ResourceArray resourceArray);
        
        /**
         * @brief Remove a player from this tile
         * @param playerId The unique identifier of the player to remove
         */
        void removePlayer(uint32_t playerId);
        
        /**
         * @brief Remove resources from this tile
         * @param resourceType The type of resource to remove
         * @param amount The quantity to remove (defaults to 1)
         */
        void removeResource(Types::ResourceType resourceType, std::size_t amount = 1);
    protected:
        Types::ResourceArray m_resources; ///< Resources on this tile
        std::unordered_map<uint32_t, std::shared_ptr<Player>> m_players; ///< Players on this tile
};
}
