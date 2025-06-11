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
, m_camera({10.0f, 6.0f, 10.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            45.0f,
            CAMERA_PERSPECTIVE)
{
    subscribeToEvents();
    initResourceMap();
}

GraphicalManager::~GraphicalManager()
{
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
    m_eventBus.subscribe<EventManager::PlayerMovedEvent>(
        [this](const EventManager::PlayerMovedEvent &event) {
            updatePlayerPosition(event);
        }
    );
    m_eventBus.subscribe<EventManager::PlayerLevelEvent>(
        [this](const EventManager::PlayerLevelEvent &event) {
            updatePlayerLevel(event);
        }
    );
    m_eventBus.subscribe<EventManager::PlayerInventoryEvent>(
        [this](const EventManager::PlayerInventoryEvent &event) {
            updatePlayerInventary(event);
        }
    );
    m_eventBus.subscribe<EventManager::PlayerResourceDropEvent>(
        [this](const EventManager::PlayerResourceDropEvent &event) {
            updatePlayerDrop(event);
        }
    );
    m_eventBus.subscribe<EventManager::PlayerResourceTakeEvent>(
        [this](const EventManager::PlayerResourceTakeEvent &event) {
            updatePlayerTake(event);
        }
    );
}

void GraphicalManager::subscribeToEvents()
{
    subscribeToMapEvents();
    subscribeToPlayerEvents();
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
    return {"", 0};
}

void GraphicalManager::loadPlayer(const EventManager::PlayerConnectionEvent &playerInfo)
{
    std::string filePath = "Source/Graphical/Assets/Player.glb";
    Vector3 graphicalPosition = { playerInfo.position.x * TILE_OFFSET, PlAYER_Y_OFFSET,
        playerInfo.position.y * TILE_OFFSET};

    m_teams[playerInfo.teamName].emplace_back(std::make_shared<GraphicalPlayer>(playerInfo.playerId,
    playerInfo.playerId, playerInfo.position, playerInfo.level, playerInfo.teamName,
        filePath, filePath, graphicalPosition, playerInfo.orientation));
}

void GraphicalManager::loadTeams(const EventManager::TeamNamesEvent &teams)
{
    for (auto team : teams.teamNames) {
        m_teams[team];
    }
}

void GraphicalManager::updatePlayerPosition(const EventManager::PlayerMovedEvent &playerMove)
{
    std::pair<std::string, std::size_t> index = getPlayerLocation(playerMove.playerId);

    m_teams[index.first][index.second].get()->setPosition(playerMove.newPosition);
    m_teams[index.first][index.second].get()->setOrientation(playerMove.newOrientation);
}

void GraphicalManager::updatePlayerLevel(const EventManager::PlayerLevelEvent &playerLevel)
{
    std::pair<std::string, std::size_t> index = getPlayerLocation(playerLevel.playerId);

    m_teams[index.first][index.second].get()->setLevel(playerLevel.newLevel);
}

void GraphicalManager::updatePlayerInventary(const EventManager::PlayerInventoryEvent &playerInventary)
{
    std::pair<std::string, std::size_t> index = getPlayerLocation(playerInventary.playerId);

    m_teams[index.first][index.second].get()->setInventory(playerInventary.inventory);
    m_teams[index.first][index.second].get()->setPosition(playerInventary.position);
}

void GraphicalManager::updatePlayerDrop(const EventManager::PlayerResourceDropEvent &playerDrop)
{
    std::pair<std::string, std::size_t> index = getPlayerLocation(playerDrop.playerId);
    Types::Position position = m_teams[index.first][index.second].get()->getPosition();

    m_map.at(position.x, position.y).addResource(playerDrop.resourceType, 1);
    m_teams[index.first][index.second].get()->removeResource(playerDrop.resourceType, 1);
}

void GraphicalManager::updatePlayerTake(const EventManager::PlayerResourceTakeEvent &playerTake)
{
    std::pair<std::string, std::size_t> index = getPlayerLocation(playerTake.playerId);
    Types::Position position = m_teams[index.first][index.second].get()->getPosition();

    m_map.at(position.x, position.y).removeResource(playerTake.resourceType, 1);
    m_teams[index.first][index.second].get()->addResource(playerTake.resourceType, 1);
}

void GraphicalManager::runRender()
{
    render();
}

void GraphicalManager::initResourceMap()
{
    m_resource.insert_or_assign(Types::ResourceType::FOOD,
        Raylib::Graphics::Model("Source/Graphical/Assets/Resources/food.obj"));
    m_resource.insert_or_assign(Types::ResourceType::LINEMATE,
        Raylib::Graphics::Model("Source/Graphical/Assets/Resources/limenate.obj"));
    m_resource.insert_or_assign(Types::ResourceType::DERAUMERE,
        Raylib::Graphics::Model("Source/Graphical/Assets/Resources/deraumere.obj"));
    m_resource.insert_or_assign(Types::ResourceType::SIBUR,
        Raylib::Graphics::Model("Source/Graphical/Assets/Resources/sibur.obj"));
    m_resource.insert_or_assign(Types::ResourceType::MENDIANE,
        Raylib::Graphics::Model("Source/Graphical/Assets/Resources/mendiane.obj"));
    m_resource.insert_or_assign(Types::ResourceType::PHIRAS,
        Raylib::Graphics::Model("Source/Graphical/Assets/Resources/phiras.obj"));
    m_resource.insert_or_assign(Types::ResourceType::THYSTAME,
        Raylib::Graphics::Model("Source/Graphical/Assets/Resources/thystame.obj"));
}

void GraphicalManager::render()
{
    while(!m_window.ShouldClose()) {
        m_camera.Update(CAMERA_FREE);
        m_window.BeginDrawing();
        m_window.ClearBackground(SKYBLUE);
        m_camera.BeginMode3D();
        renderMap();
        renderPlayers();
        //Raylib::Graphics::Shapes::DrawSphere({0.0f, 0.0f, 0.0f}, 5.0f, RED);
        m_camera.EndMode3D();
        m_window.EndDrawing();
    }
}

void GraphicalManager::renderMap()
{
    for (std::size_t x = 0; x < m_map.getWidth(); ++x) {
        for (std::size_t y = 0; y < m_map.getHeight(); ++y) {
            m_map.at(x, y).draw();
        }
    }
}

void GraphicalManager::renderPlayers()
{
    for (auto team : m_teams) {
        for (auto player : team.second) {
            player.get()->draw();
        }
    }
}
}
