/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** GameType
*/

#pragma once

#include <cstdint>
#include <array>
#include <functional>

namespace GUI {
namespace Types {

/**
 * @brief 2D position structure
 * @details Represents a position on the game map with x,y coordinates
 */
struct Position {
    int32_t x{0};  ///< X coordinate (horizontal)
    int32_t y{0};  ///< Y coordinate (vertical)
    
    /**
     * @brief Default constructor
     */
    constexpr Position() noexcept = default;
    
    /**
     * @brief Construct position with coordinates
     * @param x_ X coordinate
     * @param y_ Y coordinate
     */
    constexpr Position(int32_t x_, int32_t y_) noexcept : x(x_), y(y_) {}
    
    /**
     * @brief Equality operator
     * @param other Position to compare with
     * @return true if positions are equal
     */
    constexpr bool operator==(const Position &other) const noexcept
    {
        return x == other.x && y == other.y;
    }
    
    /**
     * @brief Inequality operator
     * @param other Position to compare with
     * @return true if positions are different
     */
    constexpr bool operator!=(const Position &other) const noexcept
    {
        return !(*this == other);
    }
    
    /**
     * @brief Addition operator
     * @param other Position to add
     * @return New position with added coordinates
     */
    constexpr Position operator+(const Position &other) const noexcept
    {
        return {x + other.x, y + other.y};
    }
    
    /**
     * @brief Subtraction operator
     * @param other Position to subtract
     * @return New position with subtracted coordinates
     */
    constexpr Position operator-(const Position &other) const noexcept
    {
        return {x - other.x, y - other.y};
    }
};

/**
 * @brief Player orientation enumeration
 * @details Represents the four cardinal directions according to protocol
 */
enum class Orientation : uint8_t {
    NORTH = 1,  ///< North direction (up)
    EAST = 2,   ///< East direction (right)
    SOUTH = 3,  ///< South direction (down)
    WEST = 4    ///< West direction (left)
};

/**
 * @brief Resource types enumeration
 * @details Matches the protocol order: q0=food, q1=linemate, etc.
 */
enum class ResourceType : uint8_t {
    FOOD = 0,       ///< Food resource (q0)
    LINEMATE = 1,   ///< Linemate stone (q1)
    DERAUMERE = 2,  ///< Deraumere stone (q2)
    SIBUR = 3,      ///< Sibur stone (q3)
    MENDIANE = 4,   ///< Mendiane stone (q4)
    PHIRAS = 5,     ///< Phiras stone (q5)
    THYSTAME = 6,   ///< Thystame stone (q6)
    COUNT = 7       ///< Total number of resource types
};

/**
 * @brief Entity type enumeration
 * @details Used for polymorphic identification of entities
 */
enum class EntityType : uint8_t {
    PLAYER,         ///< Player entity
    EGG,           ///< Egg entity
    TILE,          ///< Map tile entity
    INCANTATION   ///< Incantation entity
};

/**
 * @brief Array type for storing resource quantities
 * @details Fixed-size array matching ResourceType::COUNT
 */
using ResourceArray = std::array<uint32_t, static_cast<size_t>(ResourceType::COUNT)>;

/**
 * @brief Unique identifier types
 */
using PlayerId = uint32_t;      ///< Unique player identifier
using EggId = uint32_t;         ///< Unique egg identifier
using TeamId = uint32_t;        ///< Unique team identifier
using EntityId = uint32_t;      ///< Generic entity identifier

/**
 * @brief Time unit type
 */
using TimeUnit = float;

}
}
