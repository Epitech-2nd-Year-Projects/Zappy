/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** GameState
*/

#pragma once

#include <mutex>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include "EventManager/EventBus.hpp"
#include "EventManager/EventType.hpp"
#include "Entity/IEntity.hpp"
#include "Entity/Player/Player.hpp"
#include "Entity/MapTile/MapTile.hpp"
#include "Entity/Egg/Egg.hpp"
#include "GameState/Types/GameTypes.hpp"

namespace GUI {

/**
 * @class GameState
 * @brief Central class that manages the logical state of the game world
 *
 * The GameState class maintains the complete state of the game world,
 * including all entities (players, tiles, eggs), their relationships,
 * and properties. It receives commands from the NetworkManager that 
 * update the state based on server messages, and publishes events to 
 * notify other components about changes to the game state.
 */
class GameState {
    public:
        /**
         * @brief Constructs a GameState object
         * @param eventBus Reference to the event bus for publishing state changes
         */
        GameState(EventManager::EventBus &eventBus);
        
        /**
         * @brief Destroys the GameState object
         */
        ~GameState();

        /**
         * @brief Updates a player's position and orientation
         * @param event Event containing the player's new position and orientation
         */
        void playerMovedCommand(const EventManager::PlayerMovedEvent &event);
        
        /**
         * @brief Sets the dimensions of the game map
         * @param event Event containing the map's width and height
         */
        void mapSizeCommand(const EventManager::MapSizeEvent &event);
        
        /**
         * @brief Updates resources on a specific tile
         * @param event Event containing tile position and resource quantities
         */
        void tileContentCommand(const EventManager::TileContentEvent &event);
        
        /**
         * @brief Adds a team name to the game state
         * @param event Event containing the team name
         */
        void teamNameCommand(const EventManager::TeamNamesEvent &event);
        
        /**
         * @brief Registers a new player connection to the game
         * @param event Event containing player's initial state
         */
        void playerConnectionCommand(const EventManager::PlayerConnectionEvent &event);
        
        /**
         * @brief Updates a player's level
         * @param event Event containing player ID and new level
         */
        void playerLevelCommand(const EventManager::PlayerLevelEvent &event);
        
        /**
         * @brief Updates a player's inventory contents
         * @param event Event containing player ID and inventory state
         */
        void playerInventoryCommand(const EventManager::PlayerInventoryEvent &event);
        
        /**
         * @brief Handles a player expulsion event
         * @param event Event containing expelled player's ID
         */
        void playerExpulsionCommand(const EventManager::PlayerExpulsionEvent &event);
        
        /**
         * @brief Processes a broadcast message from a player
         * @param event Event containing sender ID and message content
         */
        void playerBroadcastCommand(const EventManager::PlayerBroadcastEvent &event);
        
        /**
         * @brief Handles the start of an incantation ritual
         * @param event Event containing incantation details
         */
        void incantationStartCommand(const EventManager::IncantationStartEvent &event);
        
        /**
         * @brief Handles the end of an incantation ritual
         * @param event Event containing incantation result
         */
        void incantationEndCommand(const EventManager::IncantationEndEvent &event);
        
        /**
         * @brief Processes a player's attempt to lay an egg
         * @param event Event containing the forking player's ID
         */
        void playerForkCommand(const EventManager::PlayerForkEvent &event);
        
        /**
         * @brief Handles a player dropping a resource
         * @param event Event containing player ID and resource type
         */
        void resourceDropCommand(const EventManager::PlayerResourceDropEvent &event);
        
        /**
         * @brief Handles a player picking up a resource
         * @param event Event containing player ID and resource type
         */
        void resourceTakeCommand(const EventManager::PlayerResourceTakeEvent &event);
        
        /**
         * @brief Processes a player's death
         * @param event Event containing the dead player's ID
         */
        void playerDeathCommand(const EventManager::PlayerDeathEvent &event);
        
        /**
         * @brief Registers a new egg laid by a player
         * @param event Event containing egg details
         */
        void eggLaidCommand(const EventManager::EggLaidEvent &event);
        
        /**
         * @brief Handles a player connecting from an egg
         * @param event Event containing egg ID
         */
        void eggConnectionCommand(const EventManager::EggConnectionEvent &event);
        
        /**
         * @brief Handles the death of an egg
         * @param event Event containing egg ID
         */
        void eggDeathCommand(const EventManager::EggDeathEvent &event);
        
        /**
         * @brief Requests the current time unit from the server
         * @param event Event containing the request details
         */
        void timeUnitRequestCommand(const EventManager::TimeUnitRequestEvent &event);
        
        /**
         * @brief Modifies the duration of a time unit
         * @param event Event containing the new time unit duration
         */
        void timeUnitModificationCommand(const EventManager::TimeUnitModificationEvent &event);
        
        /**
         * @brief Ends the game and announces the winner
         * @param event Event containing the winning team details
         */
        void gameEndCommand(const EventManager::GameEndEvent &event);
        
        /**
         * @brief Displays a message from the server to all players
         * @param event Event containing message content
         */
        void serverMessageCommand(const EventManager::ServerMessageEvent &event);

        /**
         * @brief Retrieves an entity by its unique ID
         * @param id The unique ID of the entity
         * @return Shared pointer to the IEntity interface of the entity, or nullptr if not found
         */
        std::shared_ptr<IEntity> getEntity(uint32_t id) const;
        
        /**
         * @brief Retrieves a player by their player ID
         * @param playerId The player ID
         * @return Shared pointer to the Player object, or nullptr if not found
         */
        std::shared_ptr<Player> getPlayer(Types::PlayerId playerId) const;
        
        /**
         * @brief Retrieves all players belonging to a specific team
         * @param teamName The name of the team
         * @return Vector of shared pointers to Player objects
         */
        std::vector<std::shared_ptr<Player>> getTeamPlayers(const std::string &teamName) const;
        
        /**
         * @brief Retrieves a map tile by its position
         * @param position The position of the tile
         * @return Shared pointer to the MapTile object, or nullptr if not found
         */
        std::shared_ptr<MapTile> getMapTile(const Types::Position &position) const;
        
        /**
         * @brief Retrieves an egg by its unique ID
         * @param id The unique ID of the egg
         * @return Shared pointer to the Egg object, or nullptr if not found
         */
        std::shared_ptr<Egg> getEgg(uint32_t id) const;
        
        /**
         * @brief Retrieves all server messages
         * @return Vector of strings containing server messages
         */
        std::vector<std::string> getMessagesServer() const;
        
        /**
         * @brief Retrieves the name of the winning team
         * @return String containing the winning team's name
         */
        std::string getWinnerTeam() const;
        
        /**
         * @brief Retrieves the current time unit duration
         * @return Float representing the time unit duration
         */
        float getTimeUnit() const;
    private:
        std::mutex m_mutex; /**< Mutex for synchronizing access to the game state */
        EventManager::EventBus m_eventBus; /**< Event bus for publishing state changes */
        std::unordered_map<uint32_t, std::shared_ptr<IEntity>> m_entities; /**< All entities in the game */
        std::unordered_map<Types::PlayerId, std::shared_ptr<Player>> m_players; /**< All players in the game */
        std::unordered_map<std::string, std::vector<std::shared_ptr<Player>>> m_teams; /**< All teams and their players */
        std::unordered_map<uint32_t, std::shared_ptr<Egg>> m_eggs; /**< All eggs in the game */
        std::map<Types::Position, std::shared_ptr<MapTile>> m_mapTiles; /**< All map tiles and their resources */
        std::vector<std::string> m_messagesServer; /**< Messages from the server to be displayed to players */
        std::string m_winnerTeam; /**< The team that has won the game */
        bool m_mapCreated = false; /**< Flag indicating if the map has been created */
        int m_nextEntityId = 0; /**< Counter for generating unique entity IDs */
        float m_timeUnit = 0.0f; /**< Duration of a single time unit in the game */
};
}
