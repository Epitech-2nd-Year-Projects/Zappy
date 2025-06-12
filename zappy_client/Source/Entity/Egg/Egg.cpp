/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Egg
*/

#include "Entity/Egg/Egg.hpp"

namespace GUI {
Egg::Egg(uint32_t id, Types::EggId eId, Types::Position position, std::string &teamName,
           Types::Orientation orientation)
    : AEntity(id, position, orientation)
    , m_teamName(teamName)
    , m_eggId(eId)
    , m_hatched(false)
{
}

void Egg::setHatched(bool hatched)
{
    m_hatched = hatched;
}

bool Egg::isHatched() const
{
    return m_hatched;
}

int Egg::getEggId() const
{
    return m_eggId;
}

std::string Egg::getTeamName() const
{
    return m_teamName;
}
}
