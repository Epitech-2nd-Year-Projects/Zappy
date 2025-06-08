/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** GameState
*/

#pragma once

#include <mutex>
#include <memory>
#include <vector>
#include <map>
#include "EventManager/EventBus.hpp"
#include "EventManager/EventType.hpp"
#include "Entity/IEntity.hpp"

namespace GUI {
class GameState {
    public:
        GameState();
        ~GameState();

        void playerMovedCommand(const EventManager::PlayerMovedEvent &event);

    private:
        std::mutex m_mutex;
        EventManager::EventBus m_eventBus;
        std::unordered_map<uint32_t, std::shared_ptr<IEntity>> m_entities;
};
}
