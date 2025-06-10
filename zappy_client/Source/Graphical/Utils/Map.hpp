/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Map
*/

#pragma once

#include <vector>
#include <stdexcept>
#include "Graphical/Entity/GraphicalTile.hpp"

namespace GUI {

/**
 * @class Map
 * @brief Manages the 2D grid of the game world.
 * @details Stores all tiles (GraphicalTile) in a contiguous container
 *          for optimal performance, while providing a safe and intuitive
 *          2D access interface. Can be default-constructed and initialized later.
 */
class Map {
public:
    /**
     * @brief Default constructor.
     * @details Creates an empty, uninitialized map (0x0 dimensions).
     *          The map must be initialized with `init()` before use.
     */
    Map();

    /**
     * @brief Constructs and initializes a Map object with specified dimensions.
     * @param width The width of the map.
     * @param height The height of the map.
     */
    Map(std::size_t width, std::size_t height);

    /**
     * @brief Initializes or re-initializes the map with new dimensions.
     * @details Clears any existing map data and creates a new grid.
     *          This is where the tiles are actually created.
     * @param width The new width of the map.
     * @param height The new height of the map.
     */
    void init(std::size_t width, std::size_t height);

    /**
     * @brief Accesses a tile by its coordinates (non-const version).
     * @param x The X coordinate of the tile.
     * @param y The Y coordinate of the tile.
     * @return A reference to the GraphicalTile object.
     * @throw std::out_of_range if the coordinates are out of bounds.
     */
    GraphicalTile &at(std::size_t x, std::size_t y);

    /**
     * @brief Accesses a tile by its coordinates (const version).
     * @param x The X coordinate of the tile.
     * @param y The Y coordinate of the tile.
     * @return A constant reference to the GraphicalTile object.
     * @throw std::out_of_range if the coordinates are out of bounds.
     */
    const GraphicalTile &at(std::size_t x, std::size_t y) const;

    /**
     * @brief Convenient access operator (non-const).
     * @details Allows access via `map(x, y)`. Does not perform bounds
     *          checking in release mode for performance reasons.
     */
    GraphicalTile &operator()(std::size_t x, std::size_t y);

    /**
     * @brief Convenient access operator (const).
     * @details Allows access via `map(x, y)`. Does not perform bounds
     *          checking in release mode for performance reasons.
     */
    const GraphicalTile &operator()(std::size_t x, std::size_t y) const;

    /**
     * @brief Gets the width of the map.
     * @return The map's width.
     */
    std::size_t getWidth() const noexcept;

    /**
     * @brief Gets the height of the map.
     * @return The map's height.
     */
    std::size_t getHeight() const noexcept;

private:
    std::size_t m_width;  ///< Width of the map.
    std::size_t m_height; ///< Height of the map.
    std::vector<GraphicalTile> m_tiles; ///< 1D storage of the tiles.

    class MapException : public std::exception {
    public:
        /**
         * @brief Constructs a GraphicalManagerException with a specified error message.
         * @param message A string describing the error.
         */
        MapException(const std::string &message) : message_(message) {}

        /**
         * @brief Returns a C-style character string describing the error.
         * @return A pointer to a null-terminated string.
         */
        const char *what() const noexcept override {
            return message_.c_str();
        };
    private:
        std::string message_;
    };
};
} // namespace GUI
