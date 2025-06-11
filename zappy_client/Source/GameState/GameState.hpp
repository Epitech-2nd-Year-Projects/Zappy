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
#include <unordered_map>
#include "EventManager/EventBus.hpp"
#include "EventManager/EventType.hpp"
#include "Entity/IEntity.hpp"
#include "Entity/Player/Player.hpp"
#include "Entity/MapTile/MapTile.hpp"
#include "Entity/Egg/Egg.hpp"
#include "GameState/Types/GameTypes.hpp"

namespace GUI {
class GameState {
    public:
        GameState(EventManager::EventBus &eventBus);
        ~GameState();

        void playerMovedCommand(const EventManager::PlayerMovedEvent &event);
        void mapSizeCommand(const EventManager::MapSizeEvent &event);
        void tileContentCommand(const EventManager::TileContentEvent &event);
        void teamNameCommand(const EventManager::TeamNamesEvent &event);
        void playerConnectionCommand(const EventManager::PlayerConnectionEvent &event);
        void playerLevelCommand(const EventManager::PlayerLevelEvent &event);

        std::shared_ptr<IEntity> getEntity(uint32_t id) const;
        std::shared_ptr<Player> getPlayer(Types::PlayerId playerId) const;
        std::vector<std::shared_ptr<Player>> getTeamPlayers(const std::string &teamName) const;
        std::shared_ptr<MapTile> getMapTile(const Types::Position &position) const;
        std::shared_ptr<Egg> getEgg(uint32_t id) const;
    private:
        std::mutex m_mutex;
        EventManager::EventBus m_eventBus;
        std::unordered_map<uint32_t, std::shared_ptr<IEntity>> m_entities;
        std::unordered_map<Types::PlayerId, std::shared_ptr<Player>> m_players;
        std::unordered_map<std::string, std::vector<std::shared_ptr<Player>>> m_teams;
        std::unordered_map<uint32_t, std::shared_ptr<Egg>> m_eggs;
        std::map<Types::Position, std::shared_ptr<MapTile>> m_mapTiles;
        bool m_mapCreated = false;
        int m_nextEntityId = 0;
};
}
