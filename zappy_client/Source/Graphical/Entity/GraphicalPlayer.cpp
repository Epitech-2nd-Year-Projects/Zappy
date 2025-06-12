/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** GraphicalPlayer
*/

#include <iostream>
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
    playIdleAnimation();
}

GraphicalPlayer::~GraphicalPlayer()
{
}

void GraphicalPlayer::update()
{
    m_animation.Update(m_model);
    if (m_animation.IsOneShotFinished())
        playIdleAnimation();
}

void GraphicalPlayer::draw() const
{
    m_model.Draw(m_graphicPosition, m_scale, WHITE);   
}

void GraphicalPlayer::playIdleAnimation()
{
    if (!m_animation.HasAnimations())
        return;
    for (int i = 0; i < m_animation.GetAnimationCount(); ++i) {
        if (m_animation.GetAnimationName(i) == "Idle_Loop") {
            if (m_animation.GetCurrentAnimIndex() != i) {
                m_animation.Play(i, true);
            }
            break;
        }
    }
}

void GraphicalPlayer::playIncantationAnimation()
{
    if (!m_animation.HasAnimations())
        return;
    for (int i = 0; i < m_animation.GetAnimationCount(); ++i) {
        if (m_animation.GetAnimationName(i) == "Dance_Loop") {
            m_animation.Play(i, true);
            break;
        }
    }
}

Vector3 GraphicalPlayer::getGraphicalPosition() const
{
    return m_graphicPosition;
}
}
