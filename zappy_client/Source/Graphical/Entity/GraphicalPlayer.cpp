/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** GraphicalPlayer
*/

#include "Graphical/Entity/GraphicalPlayer.hpp"

namespace GUI {

GraphicalPlayer::GraphicalPlayer(uint32_t id, Types::PlayerId pId, Types::Position position,
                uint32_t level, const std::string &teamName, const std::string &modelName,
                const std::string &animationName, Vector3 graphicPosition,
                Types::Orientation orientation)
                : Player(id, pId, position, level, teamName, orientation)
                , m_model(modelName)
                , m_animation(animationName)
                , m_graphicPosition(graphicPosition)
                , m_scale(PLAYER_SCALE)
{
}

GraphicalPlayer::~GraphicalPlayer()
{
}

void GraphicalPlayer::draw() const
{
    m_model.Draw(m_graphicPosition, m_scale, WHITE);   
}
}