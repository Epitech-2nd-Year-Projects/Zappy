/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** EventType
*/

#pragma once

#include "EventManager/IEvent.hpp"
#include "GameState/Types/GameTypes.hpp"

namespace GUI {
namespace EventManager {

// Map Events
/**
 * @brief Map size event (msz command)
 * @details Triggered when the server sends map dimensions
 */
struct MapSizeEvent : public IEvent {
    uint32_t width;   ///< Map width
    uint32_t height;  ///< Map height
};

/**
 * @brief Tile content event (bct command)
 * @details Triggered when the server sends content of a specific tile
 */
struct TileContentEvent : public IEvent {
    Types::Position position;        ///< Tile position
    Types::ResourceArray resources;  ///< Resource quantities on tile
};

/**
 * @brief Map content event (mct command)
 * @details Triggered when the server sends content of all tiles
 */
struct MapContentEvent : public IEvent {
    std::vector<Types::Position> positions;           ///< All tile positions
    std::vector<Types::ResourceArray> resourceArrays; ///< Resource arrays for each tile
};

/**
 * @brief Team names event (tna command)
 * @details Triggered when the server sends names of all teams
 */
struct TeamNamesEvent : public IEvent {
    std::string teamNames; ///< Team names
};

// Player Events

/**
 * @brief Player connection event (pnw command)
 * @details Triggered when a new player connects to the game
 */
struct PlayerConnectionEvent : public IEvent {
    Types::PlayerId playerId;        ///< Player unique ID
    Types::Position position;        ///< Initial position
    Types::Orientation orientation;  ///< Initial orientation
    Types::PlayerLvl level;         ///< Initial level
    std::string teamName;           ///< Team name
};

/**
 * @brief Player moved event (ppo command)
 * @details Triggered when a player changes position or orientation
 */
struct PlayerMovedEvent : public IEvent {
    Types::PlayerId playerId;           ///< Player ID
    Types::Position newPosition;        ///< New position
    Types::Orientation newOrientation;  ///< New orientation
};

/**
 * @brief Player level event (plv command)
 * @details Triggered when a player's level changes
 */
struct PlayerLevelEvent : public IEvent {
    Types::PlayerId playerId;   ///< Player ID
    Types::PlayerLvl newLevel;  ///< New level
};

/**
 * @brief Player inventory event (pin command)
 * @details Triggered when requesting player's inventory
 */
struct PlayerInventoryEvent : public IEvent {
    Types::PlayerId playerId;        ///< Player ID
    Types::Position position;        ///< Player position
    Types::ResourceArray inventory;  ///< Player inventory
};

/**
 * @brief Player expulsion event (pex command)
 * @details Triggered when a player is expelled from a tile
 */
struct PlayerExpulsionEvent : public IEvent {
    Types::PlayerId playerId; ///< Expelled player ID
};

/**
 * @brief Player broadcast event (pbc command)
 * @details Triggered when a player broadcasts a message
 */
struct PlayerBroadcastEvent : public IEvent {
    Types::PlayerId senderId; ///< Sender player ID
    std::string message;      ///< Broadcast message
};

/**
 * @brief Player fork event (pfk command)
 * @details Triggered when a player lays an egg
 */
struct PlayerForkEvent : public IEvent {
    Types::PlayerId playerId; ///< Player ID who laid the egg
};

/**
 * @brief Player resource drop event (pdr command)
 * @details Triggered when a player drops a resource
 */
struct PlayerResourceDropEvent : public IEvent {
    Types::PlayerId playerId;           ///< Player ID
    Types::ResourceType resourceType;   ///< Type of resource dropped
};

/**
 * @brief Player resource take event (pgt command)
 * @details Triggered when a player picks up a resource
 */
struct PlayerResourceTakeEvent : public IEvent {
    Types::PlayerId playerId;           ///< Player ID
    Types::ResourceType resourceType;   ///< Type of resource taken
};

/**
 * @brief Player death event (pdi command)
 * @details Triggered when a player dies
 */
struct PlayerDeathEvent : public IEvent {
    Types::PlayerId playerId; ///< Dead player ID
};

// Incantation Events

/**
 * @brief Incantation start event (pic command)
 * @details Triggered when an incantation ritual begins
 */
struct IncantationStartEvent : public IEvent {
    Types::Position position;                ///< Incantation position
    Types::PlayerLvl level;                 ///< Incantation level
    std::vector<Types::PlayerId> participants; ///< Participating players
};

/**
 * @brief Incantation end event (pie command)
 * @details Triggered when an incantation ritual ends
 */
struct IncantationEndEvent : public IEvent {
    Types::Position position; ///< Incantation position
    bool result;             ///< Success (true) or failure (false)
};

// Egg Events

/**
 * @brief Egg laid event (enw command)
 * @details Triggered when an egg is laid by a player
 */
struct EggLaidEvent : public IEvent {
    Types::EggId eggId;        ///< Egg unique ID
    Types::PlayerId parentId;  ///< Parent player ID
    Types::Position position;  ///< Egg position
};

/**
 * @brief Egg connection event (ebo command)
 * @details Triggered when a player connects to an egg
 */
struct EggConnectionEvent : public IEvent {
    Types::EggId eggId; ///< Egg ID that hatched
};

/**
 * @brief Egg death event (edi command)
 * @details Triggered when an egg is destroyed
 */
struct EggDeathEvent : public IEvent {
    Types::EggId eggId; ///< Dead egg ID
};

// Time Events

/**
 * @brief Time unit request event (sgt command)
 * @details Triggered when requesting current time unit
 */
struct TimeUnitRequestEvent : public IEvent {
    Types::TimeUnit timeUnit; ///< Current time unit
};

/**
 * @brief Time unit modification event (sst command)
 * @details Triggered when time unit is modified
 */
struct TimeUnitModificationEvent : public IEvent {
    Types::TimeUnit newTimeUnit; ///< New time unit value
};

// Game Events

/**
 * @brief Game end event (seg command)
 * @details Triggered when the game ends
 */
struct GameEndEvent : public IEvent {
    std::string winningTeam; ///< Name of winning team
};

/**
 * @brief Server message event (smg command)
 * @details Triggered when server sends a message
 */
struct ServerMessageEvent : public IEvent {
    std::string message; ///< Server message
};

// Error Events

/**
 * @brief Unknown command event (suc command)
 * @details Triggered when an unknown command is sent
 */
struct UnknownCommandEvent : public IEvent {
    std::string command; ///< Unknown command that was sent
};

/**
 * @brief Bad parameter event (sbp command)
 * @details Triggered when a command has bad parameters
 */
struct BadParameterEvent : public IEvent {
    std::string parameter; ///< Bad parameter that was sent
};
}
}
