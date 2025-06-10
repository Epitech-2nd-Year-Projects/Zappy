/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** GameState
*/

#include <iostream>
#include "GameState/GameState.hpp"

namespace GUI {
GameState::GameState(EventManager::EventBus &eventBus)
    : m_eventBus(eventBus)
{
}

GameState::~GameState()
{
}

void GameState::playerMovedCommand(const EventManager::PlayerMovedEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_entities.find(event.playerId);

    if (it != m_entities.end()) {
        auto &entity = it->second;
        if (entity) {
            entity->setPosition(event.newPosition);
            entity->setOrientation(event.newOrientation);
        }
        m_eventBus.publish(event);
    } else {
        std::cout << "Player with ID " << event.playerId << " not found in game state." << std::endl;
    }
}

std::shared_ptr<IEntity> GameState::getEntity(uint32_t id) const
{
    auto it = m_entities.find(id);

    if (it != m_entities.end())
        return it->second;
    return nullptr;
}

std::shared_ptr<Player> GameState::getPlayer(Types::PlayerId playerId) const
{
    auto it = m_players.find(playerId);

    if (it != m_players.end())
        return it->second;
    return nullptr;
}

std::vector<std::shared_ptr<Player>> GameState::getTeamPlayers(const std::string &teamName) const
{
    auto it = m_teams.find(teamName);

    if (it != m_teams.end())
        return it->second;
    return {};
}

std::shared_ptr<MapTile> GameState::getMapTile(const Types::Position &position) const
{
    auto it = m_mapTiles.find(position);

    if (it != m_mapTiles.end())
        return it->second;
    return nullptr;
}

std::shared_ptr<Egg> GameState::getEgg(uint32_t id) const
{
    auto it = m_eggs.find(id);

    if (it != m_eggs.end())
        return it->second;
    return nullptr;
}

}
