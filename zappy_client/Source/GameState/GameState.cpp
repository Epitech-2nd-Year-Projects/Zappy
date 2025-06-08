/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** GameState
*/

#include <iostream>
#include "GameState/GameState.hpp"

namespace GUI {
GameState::GameState()
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
}
