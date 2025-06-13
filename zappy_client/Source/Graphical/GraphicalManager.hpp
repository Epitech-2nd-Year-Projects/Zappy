/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** GraphicalManager
*/

#pragma once

#include <cstdio>
#include <string>
#include <map>
#include <memory>
#include <utility>
#include <optional>
#include "Raylib/Core/Window.hpp"
#include "Raylib/Graphics/Camera.hpp"
#include "Graphical/Types/GraphicalTypes.hpp"
#include "EventManager/EventBus.hpp"
#include "EventManager/EventType.hpp"
#include "Graphical/Entity/GraphicalTile.hpp"
#include "Graphical/Entity/GraphicalPlayer.hpp"
#include "Graphical/Utils/Map.hpp"
#include "Raylib/Core/Input.hpp"

namespace GUI {

    constexpr std::size_t DEFAULT_WINDOW_WIDTH = 1920;
    constexpr std::size_t DEFAULT_WINDOW_HEIGHT = 1080;

class GraphicalManager {
public:
    GraphicalManager(std::shared_ptr<EventManager::EventBus> eventBus);
    ~GraphicalManager();

    void runRender();

private:
    std::shared_ptr<EventManager::EventBus> m_eventBus;
    WindowInformation m_windowInfo;
    Raylib::Core::Window m_window;
    Raylib::Graphics::Camera m_camera;

    Map m_map;
    std::map<std::string, std::vector<std::shared_ptr<GraphicalPlayer>>> m_teams;
    std::map<Types::ResourceType, Raylib::Graphics::Model> m_resource;
    std::optional<std::pair<std::size_t, std::size_t>> m_selectedTileCoords;
    std::shared_ptr<GraphicalPlayer> m_selectedPlayer;
    bool m_showTileInfo;
    bool m_showPlayerInfo;

    void CheckObjectClicked();
    void CheckMapTileClicked();
    void CheckPlayerClicked();
    void renderSelectedTileBorder();
    void renderSelectedPlayerBorder();
    void renderTileInfoUI();
    void renderPlayerInfoUI();
    void renderTeamInfoUI();
    std::string getTileInfoText(const GraphicalTile &tile) const;
    std::string getPlayerInfoText(const GraphicalPlayer &player) const;
    std::string getTeamInfoText(const std::string &teamName) const;

    void render();
    void renderMap();
    void renderPlayers();
    void initResourceMap();
    void renderResource(std::size_t x, std::size_t y);
    void renderMapResources();

    void subscribeToEvents();
    void subscribeToMapEvents();
    void subscribeToPlayerEvents();
    void initMap(std::size_t width, std::size_t height);
    void addMapRessources(const EventManager::MapContentEvent &mapContent);
    void loadTeams(const EventManager::TeamNamesEvent &teams);
    void loadPlayer(const EventManager::PlayerConnectionEvent &playerInfo);
    void updatePlayerPosition(const EventManager::PlayerMovedEvent &playerMove);
    void updatePlayerLevel(const EventManager::PlayerLevelEvent &playerLevel);
    void updatePlayerInventary(const EventManager::PlayerInventoryEvent &playerInventary);
    void updatePlayerDrop(const EventManager::PlayerResourceDropEvent &playerDrop);
    void updatePlayerTake(const EventManager::PlayerResourceTakeEvent &playerTake);
    void updatePlayerDeath(const EventManager::PlayerDeathEvent &playerDeath);
    void updatePlayersIncantationStart(const EventManager::IncantationStartEvent &incantation);
    void updatePlayersIncantationEnd(const EventManager::IncantationEndEvent &incantation);
    std::pair<std::string, std::size_t> getPlayerLocation(uint32_t id);

    class GraphicalManagerException : public std::exception {
    public:
        /**
         * @brief Constructs a GraphicalManagerException with a specified error message.
         * @param message A string describing the error.
         */
        GraphicalManagerException(const std::string &message) : message_(message) {}

        /**
         * @brief Returns a C-style character string describing the error.
         * @return A pointer to a null-terminated string.
         */
        const char *what() const noexcept override {
            return message_.c_str();
        };
    private:
        std::string message_;
    };
};
}
