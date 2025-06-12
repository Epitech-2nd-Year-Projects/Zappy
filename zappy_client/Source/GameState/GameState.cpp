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

void GameState::mapSizeCommand(const EventManager::MapSizeEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_mapCreated) {
        m_eventBus.publish(event);
        return;
    }
    m_mapTiles.clear();
    for (uint32_t x = 0; x < event.width; ++x) {
        for (uint32_t y = 0; y < event.height; ++y) {
            Types::Position position(x, y);
            auto tile = std::make_shared<MapTile>(m_nextEntityId++, position);
            m_mapTiles[position] = tile;
            m_entities[tile->getId()] = tile;
        }
    }
    m_mapCreated = true;
    m_eventBus.publish(event);
}

void GameState::tileContentCommand(const EventManager::TileContentEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_mapTiles.find(event.position);

    if (it == m_mapTiles.end() || !it->second) {
        std::cerr << "Tile at position (" << event.position.x << ", " << event.position.y
                  << ") not found in game state." << std::endl;
        return;
    }
    auto &tile = it->second;
    tile->setResource(event.resources);
    m_eventBus.publish(event);
}

void GameState::teamNameCommand(const EventManager::TeamNamesEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_teams.find(event.teamNames) != m_teams.end())
        return;
    m_teams[event.teamNames] = {};
    m_eventBus.publish(event);
}

void GameState::playerConnectionCommand(const EventManager::PlayerConnectionEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto player = std::make_shared<Player>(m_nextEntityId++, event.playerId, event.position,
                                           event.level, event.teamName, event.orientation);

    m_entities[player->getId()] = player;
    m_players[event.playerId] = player;
    m_teams[event.teamName].push_back(player);
    m_eventBus.publish(event);
}

void GameState::playerLevelCommand(const EventManager::PlayerLevelEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_players.find(event.playerId);

    if (it == m_players.end() || !it->second) {
        std::cerr << "Player with ID " << event.playerId << " not found in game state." << std::endl;
        return;
    }
    auto &player = it->second;
    player->setLevel(event.newLevel);
    m_eventBus.publish(event);
}

void GameState::playerInventoryCommand(const EventManager::PlayerInventoryEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_players.find(event.playerId);

    if (it == m_players.end() || !it->second) {
        std::cerr << "Player with ID " << event.playerId << " not found in game state." << std::endl;
        return;
    }
    auto &player = it->second;
    player->setInventory(event.inventory);
    player->setPosition(event.position);
    m_eventBus.publish(event);
}

void GameState::playerExpulsionCommand(const EventManager::PlayerExpulsionEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_eventBus.publish(event);
}

void GameState::playerBroadcastCommand(const EventManager::PlayerBroadcastEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_players.find(event.senderId);

    if (it == m_players.end() || !it->second) {
        std::cerr << "Player with ID " << event.senderId << " not found in game state." << std::endl;
        return;
    }
    m_eventBus.publish(event);
}

void GameState::incantationStartCommand(const EventManager::IncantationStartEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_eventBus.publish(event);
}

void GameState::incantationEndCommand(const EventManager::IncantationEndEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_eventBus.publish(event);
}

void GameState::playerForkCommand(const EventManager::PlayerForkEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_players.find(event.playerId);

    if (it == m_players.end() || !it->second) {
        std::cerr << "Player with ID " << event.playerId << " not found in game state." << std::endl;
        return;
    }
    m_eventBus.publish(event);
}

void GameState::resourceDropCommand(const EventManager::PlayerResourceDropEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_players.find(event.playerId);

    if (it == m_players.end() || !it->second) {
        std::cerr << "Player with ID " << event.playerId << " not found in game state for resource drop command." << std::endl;
        return;
    }
    auto player = it->second;
    player->removeResource(event.resourceType);
    m_eventBus.publish(event);
}

void GameState::resourceTakeCommand(const EventManager::PlayerResourceTakeEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_players.find(event.playerId);

    if (it == m_players.end() || !it->second) {
        std::cerr << "Player with ID " << event.playerId << " not found in game state for resource take command." << std::endl;
        return;
    }
    auto player = it->second;
    player->addResource(event.resourceType);
    m_eventBus.publish(event);
}

void GameState::playerDeathCommand(const EventManager::PlayerDeathEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_players.find(event.playerId);

    if (it == m_players.end() || !it->second) {
        std::cerr << "Player with ID " << event.playerId << " not found in game state for player death command." << std::endl;
        return;
    }
    auto player = it->second;
    player->setAlive(false);
    m_eventBus.publish(event);
}

void GameState::eggLaidCommand(const EventManager::EggLaidEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_players.find(event.parentId);

    if (it == m_players.end() || !it->second) {
        std::cerr << "Player with ID " << event.parentId << " not found in game state for egg laid command." << std::endl;
        return;
    }
    auto player = it->second;
    std::string teamName = player->getTeamName();
    auto egg = std::make_shared<Egg>(m_nextEntityId++, event.eggId, event.position, teamName);
    m_eggs[event.eggId] = egg;
    m_entities[egg->getId()];
    m_eventBus.publish(event);
}

void GameState::eggConnectionCommand(const EventManager::EggConnectionEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_eggs.find(event.eggId);

    if (it == m_eggs.end() || !it->second) {
        std::cerr << "Egg with ID " << event.eggId << " not found in game state for egg connection command." << std::endl;
        return;
    }
    auto egg = it->second;
    egg->setHatched(true);
    m_eventBus.publish(event);
}

void GameState::eggDeathCommand(const EventManager::EggDeathEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_eggs.find(event.eggId);

    if (it == m_eggs.end() || !it->second) {
        std::cerr << "Egg with ID " << event.eggId << " not found in game state for egg death command." << std::endl;
        return;
    }
    auto egg = it->second;
    egg->setAlive(false);
    m_eventBus.publish(event);
}

void GameState::timeUnitRequestCommand(const EventManager::TimeUnitRequestEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_timeUnit = event.timeUnit;
    m_eventBus.publish(event);
}

void GameState::timeUnitModificationCommand(const EventManager::TimeUnitModificationEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_timeUnit = event.newTimeUnit;
    m_eventBus.publish(event);
}

void GameState::gameEndCommand(const EventManager::GameEndEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_winnerTeam = event.winningTeam;
    m_eventBus.publish(event);
}

void GameState::serverMessageCommand(const EventManager::ServerMessageEvent &event)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_messagesServer.push_back(event.message);
    m_eventBus.publish(event);
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

std::vector<std::string> GameState::getMessagesServer() const
{
    return m_messagesServer;
}

std::shared_ptr<Egg> GameState::getEgg(uint32_t id) const
{
    auto it = m_eggs.find(id);

    if (it != m_eggs.end())
        return it->second;
    return nullptr;
}

std::string GameState::getWinnerTeam() const
{
    return m_winnerTeam;
}
}
