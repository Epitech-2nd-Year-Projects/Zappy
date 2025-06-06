/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** ProtocolTypes
*/

#pragma once

#include <string>
#include <vector>
#include <optional>
#include "GameTypes.hpp"

namespace GUI {
namespace Types {
/**
* @brief Map size command data (msz)
 */
struct MapSizeData {
    uint32_t width;   ///< Map width
    uint32_t height;  ///< Map height
};

/**
 * @brief Tile content command data (bct)
 */
struct TileContentData {
    Position position;           ///< Tile position
    ResourceArray resources;     ///< Resource quantities on tile
};

/**
 * @brief Player connection command data (pnw)
 */
struct PlayerConnectionData {
    PlayerId playerId;           ///< Player unique ID
    Position position;           ///< Initial position
    Orientation orientation;     ///< Initial orientation
    uint32_t level;             ///< Initial level
    std::string teamName;       ///< Team name
};

/**
 * @brief Player position command data (ppo)
 */
struct PlayerPositionData {
    PlayerId playerId;           ///< Player ID
    Position position;           ///< New position
    Orientation orientation;     ///< New orientation
};

/**
 * @brief Player level command data (plv)
 */
struct PlayerLevelData {
    PlayerId playerId;           ///< Player ID
    uint32_t level;             ///< New level
};

/**
 * @brief Player inventory command data (pin)
 */
struct PlayerInventoryData {
    PlayerId playerId;           ///< Player ID
    Position position;           ///< Player position
    ResourceArray inventory;     ///< Player inventory
};

/**
 * @brief Incantation start command data (pic)
 */
struct IncantationStartData {
    Position position;                   ///< Incantation position
    uint32_t level;                     ///< Incantation level
    std::vector<PlayerId> participants; ///< Participating players
};

/**
 * @brief Incantation end command data (pie)
 */
struct IncantationEndData {
    Position position;           ///< Incantation position
    bool result;                ///< Success (true) or failure (false)
};

/**
 * @brief Broadcast command data (pbc)
 */
struct BroadcastData {
    PlayerId senderId;           ///< Sender player ID
    std::string message;         ///< Broadcast message
};

/**
 * @brief Egg laid command data (enw)
 */
struct EggLaidData {
    EggId eggId;                ///< Egg unique ID
    PlayerId parentId;          ///< Parent player ID
    Position position;          ///< Egg position
};

/**
 * @brief Game end command data (seg)
 */
struct GameEndData {
    std::string winningTeam;    ///< Name of winning team
};

/**
 * @brief Time unit command data (sgt/sst)
 */
struct TimeUnitData {
    TimeUnit timeUnit;          ///< Current time unit
};

}
}
