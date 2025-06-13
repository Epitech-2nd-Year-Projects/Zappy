/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** GraphicalTile
*/

#include "Graphical/Entity/GraphicalTile.hpp"

namespace GUI {

GraphicalTile::GraphicalTile(uint32_t id, Types::Position position,
            const std::string &modelName, Vector3 graphicPosition,
            Types::Orientation orientation)
            : MapTile(id, position, orientation)
            , m_model(modelName)
            , m_graphicPosition(graphicPosition)
            , m_scale(TILE_SCALE)
{
}

GraphicalTile::~GraphicalTile()
{
}

void GraphicalTile::draw() const
{
    m_model.Draw(m_graphicPosition, m_scale, WHITE);
}

Vector3 GraphicalTile::getGraphicalPosition() const
{
    return m_graphicPosition;
}
}
