/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** AEntity
*/

#include "Entity/AEntity.hpp"

namespace GUI {
AEntity::AEntity(std::shared_ptr<Types::Position> position, uint32_t id,
                 std::unique_ptr<Raylib::Graphics::Animation> animation,
                 std::unique_ptr<Raylib::Graphics::Model> model)
    : m_position(std::move(position))
    , m_id(id)
    , m_animation(std::move(animation))
    , m_model(std::move(model))
{}

void AEntity::draw() const
{
}

void AEntity::update()
{
}

void AEntity::setPosition(Types::Position position)
{

}

void AEntity::setOrientation(Types::Orientation orientation)
{
}
}
