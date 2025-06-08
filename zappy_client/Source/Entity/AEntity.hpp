/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** AEntity
*/

#pragma once

#include <memory>
#include "Entity/IEntity.hpp"
#include "GameState/Types/ProtocolTypes.hpp"
#include "Raylib/Graphics/Animation.hpp"

namespace GUI {
class AEntity : public IEntity {
    public:
        AEntity(std::shared_ptr<Types::Position> position, uint32_t id,
                std::unique_ptr<Raylib::Graphics::Animation> animation,
                std::unique_ptr<Raylib::Graphics::Model> model);
        ~AEntity() = default;

        void draw() const override;
        void update() override;

        void setPosition(Types::Position position) override;
        void setOrientation(Types::Orientation orientation) override;
    protected:
        std::shared_ptr<Types::Position> m_position;
        uint32_t m_id;
        std::unique_ptr<Raylib::Graphics::Animation> m_animation;
        std::unique_ptr<Raylib::Graphics::Model> m_model;
};
}
