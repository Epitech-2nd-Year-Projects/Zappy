/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** AEntity
*/

#include "Entity/AEntity.hpp"

namespace GUI {
AEntity::AEntity(uint32_t id, Types::Position position,
                 Types::Orientation orientation)
    : m_id(id)
    , m_position(position)
    , m_orientation(orientation)
{}

void AEntity::setPosition(Types::Position position)
{
    m_position = position;
}

void AEntity::setOrientation(Types::Orientation orientation)
{
    m_orientation = orientation;
}
}
