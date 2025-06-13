/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Map
*/

#include <cassert>
#include "Map.hpp"

namespace GUI {

Map::Map() : m_width(0), m_height(0)
{
}

Map::Map(std::size_t width, std::size_t height)
{
    init(width, height);
}

void Map::init(std::size_t width, std::size_t height)
{
    uint32_t id = 0;
    Types::Position logicalPos(0, 0);
    Vector3 graphicPos = {0, 0, 0};
    std::string modelName;
    m_tiles.clear();
    m_width = width;
    m_height = height;
    if (width == 0 || height == 0)
        return;
    m_tiles.reserve(width * height);
    for (std::size_t y = 0; y < height; ++y) {
        for (std::size_t x = 0; x < width; ++x) {
            id = y * width + x;
            logicalPos = {static_cast<int32_t>(x), static_cast<int32_t>(y)};
            graphicPos = {static_cast<float>(x * TILE_SPACING), 0.0f, static_cast<float>(y * TILE_SPACING)};
            modelName = "Source/Graphical/Assets/Map_Island.glb";
            m_tiles.emplace_back(id, logicalPos, modelName, graphicPos);
        }
    }
}

GraphicalTile &Map::at(std::size_t x, std::size_t y)
{
    if (x >= m_width || y >= m_height)
        throw MapException("Map coordinates are out of range.");
    return m_tiles[y * m_width + x];
}

const GraphicalTile &Map::at(std::size_t x, std::size_t y) const
{
    if (x >= m_width || y >= m_height)
        throw MapException("Map coordinates are out of range.");
    return m_tiles[y * m_width + x];
}

GraphicalTile &Map::operator()(std::size_t x, std::size_t y)
{
    assert(x < m_width && y < m_height && "Map coordinates out of range");
    return m_tiles[y * m_width + x];
}

const GraphicalTile &Map::operator()(std::size_t x, std::size_t y) const
{
    assert(x < m_width && y < m_height && "Map coordinates out of range");
    return m_tiles[y * m_width + x];
}

std::size_t Map::getWidth() const noexcept
{
    return m_width;
}

std::size_t Map::getHeight() const noexcept
{
    return m_height;
}
} // namespace GUI
