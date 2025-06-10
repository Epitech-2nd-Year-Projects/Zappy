/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** GraphicalPLayer
*/

#pragma once

#include "Raylib/Graphics/Model.hpp"
#include "Raylib/Graphics/Animation.hpp"
#include "Entity/Player/Player.hpp"

namespace GUI {

    constexpr float PLAYER_SCALE = 0.35f;
    constexpr float PlAYER_Y_OFFSET = 0.0f;
    constexpr float TILE_OFFSET = 5.0f;

class GraphicalPlayer : public Player {
    public:
        GraphicalPlayer(uint32_t id, Types::PlayerId pId, Types::Position position,
                uint32_t level, const std::string &teamName, const std::string &modelName, const std::string &animationName, 
                Vector3 graphicPosition, Types::Orientation orientation = Types::Orientation::NORTH);
        ~GraphicalPlayer();

        void draw() const override;

        Raylib::Graphics::Model m_model;
        Raylib::Graphics::Animation m_animation;
    protected:
        Vector3 m_graphicPosition;
        float m_scale;
};
}
