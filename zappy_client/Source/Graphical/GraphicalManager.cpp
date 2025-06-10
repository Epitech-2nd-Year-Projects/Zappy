/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** GraphicalManager
*/

#include "GraphicalManager.hpp"
#include "Raylib/Graphics/Shapes.hpp"


namespace GUI {

GraphicalManager::GraphicalManager(EventManager::EventBus &eventBus)
: m_eventBus(eventBus)
, m_windowInfo({"Zappy", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT})
, m_window(m_windowInfo.windowWidth, m_windowInfo.windowHeight, m_windowInfo.windowName)
, m_camera({10.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            45.0f,
            CAMERA_PERSPECTIVE)
{
    subscribeToEvents();
}

GraphicalManager::~GraphicalManager()
{
}

void GraphicalManager::render()
{
    while(!m_window.ShouldClose()) {
        m_camera.Update(CAMERA_FREE);
        m_window.BeginDrawing();
        m_window.ClearBackground(SKYBLUE);
        m_camera.BeginMode3D();
        Raylib::Graphics::Shapes::DrawSphere({0.0f, 0.0f, 0.0f}, 5.0f, RED);
        m_camera.EndMode3D();
        m_window.EndDrawing();
    }
}

void GraphicalManager::subscribeToMapEvents()
{
    m_eventBus.subscribe<EventManager::MapSizeEvent>(
        [this](const EventManager::MapSizeEvent &event) {
            initMap(event.width, event.height);
        }
    );
    m_eventBus.subscribe<EventManager::TileContentEvent>(
        [this](const EventManager::TileContentEvent &event) {
            m_map.at(event.position.x, event.position.y).addResource(event.resources);
        }
    );
    m_eventBus.subscribe<EventManager::MapContentEvent>(
        [this](const EventManager::MapContentEvent &event) {
            addMapRessources(event);
        }
    );
}

void GraphicalManager::subscribeToPlayerEvents()
{
    m_eventBus.subscribe<EventManager::TeamNamesEvent>(
        [this](const EventManager::TeamNamesEvent &event) {
            loadTeams(event);
        }
    );
    m_eventBus.subscribe<EventManager::PlayerConnectionEvent>(
        [this](const EventManager::PlayerConnectionEvent &event) {
            loadPlayer(event);
        }
    );
}

void GraphicalManager::subscribeToEvents()
{
    subscribeToMapEvents();
}

void GraphicalManager::initMap(std::size_t width, std::size_t height)
{
    m_map.init(width, height);
}

void GraphicalManager::addMapRessources(const EventManager::MapContentEvent &mapContent)
{
    for (std::size_t i = 0; i < mapContent.positions.size(); ++i) {
        m_map.at(mapContent.positions[i].x, mapContent.positions[i].x).addResource(
            mapContent.resourceArrays[i]);
    }
}

std::pair<std::string, std::size_t> GraphicalManager::getPlayerLocation(uint32_t id)
{
    for (auto element : m_teams) {
        for (std::size_t i = 0;  i < element.second.size(); ++i) {
            if (element.second[i].get()->getPlayerId() == id)
                return {element.first, i};
        }
    }
}

void GraphicalManager::loadPlayer(const EventManager::PlayerConnectionEvent &playerInfo)
{
    Vector3 graphicalPosition = { playerInfo.position.x * TILE_OFFSET, PlAYER_Y_OFFSET,
        playerInfo.position.y * TILE_OFFSET};

    m_teams[playerInfo.teamName].emplace_back(std::make_shared<GraphicalPlayer>(playerInfo.playerId,
    playerInfo.playerId, playerInfo.position, playerInfo.level, playerInfo.teamName,
        "Assets/Player.glb", "Assets/Player.glb", graphicalPosition, playerInfo.orientation));
}

void GraphicalManager::loadTeams(const EventManager::TeamNamesEvent &teams)
{
    for (auto team : teams.teamNames) {
        m_teams[team];
    }
}

void GraphicalManager::runRender()
{
    render();
}

}
