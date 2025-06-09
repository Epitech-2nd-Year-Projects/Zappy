/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Island
*/

#include "Entity/MapTile/MapTile.hpp"

namespace GUI {
MapTile::MapTile(uint32_t id, Types::Position position,
                 Types::Orientation orientation)
    : AEntity(id, position, orientation)
{
}

MapTile::~MapTile()
{
}

Types::ResourceArray MapTile::getResources() const
{
    return m_resources;
}

std::size_t MapTile::getNbPlayers() const
{
    return m_players.size();
}

void MapTile::addPlayer(uint32_t playerId, std::shared_ptr<Player> player)
{
    m_players[playerId] = player;
}

void MapTile::removePlayer(uint32_t playerId)
{
    m_players.erase(playerId);
}

void MapTile::addResource(Types::ResourceType resourceType, std::size_t amount)
{
    if (resourceType < Types::ResourceType::COUNT) {
        m_resources[static_cast<size_t>(resourceType)] += amount;
    }
}

void MapTile::removeResource(Types::ResourceType resourceType, std::size_t amount)
{
    if (resourceType >= Types::ResourceType::COUNT)
        return;
    auto &resourceCount = m_resources[static_cast<size_t>(resourceType)];
    if (resourceCount >= amount) {
        resourceCount -= amount;
    } else {
        resourceCount = 0;
    }
}
}
