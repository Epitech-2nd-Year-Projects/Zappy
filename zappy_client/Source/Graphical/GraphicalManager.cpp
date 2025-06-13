/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** GraphicalManager
*/

#include <float.h>
#include <sstream>
#include "GraphicalManager.hpp"
#include "Raylib/Graphics/Shapes.hpp"

namespace GUI {

GraphicalManager::GraphicalManager(std::shared_ptr<EventManager::EventBus> eventBus)
: m_eventBus(eventBus)
, m_windowInfo({"Zappy", DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT})
, m_window(m_windowInfo.windowWidth, m_windowInfo.windowHeight, m_windowInfo.windowName)
, m_camera({10.0f, 6.0f, 10.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            45.0f,
            CAMERA_PERSPECTIVE)
, m_selectedTileCoords(std::nullopt)
, m_showTileInfo(false)
{
    subscribeToEvents();
    initResourceMap();
}

GraphicalManager::~GraphicalManager()
{
}

void GraphicalManager::runRender()
{
    render();
}

void GraphicalManager::render()
{
    while(!m_window.ShouldClose()) {
        m_camera.Update(CAMERA_FREE);
        CheckObjectClicked();
        m_window.BeginDrawing();
        m_window.ClearBackground(SKYBLUE);
        m_camera.BeginMode3D();
        renderMap();
        renderPlayers();
        renderMapResources();
        renderSelectedTileBorder();
        renderSelectedPlayerBorder();
        m_camera.EndMode3D();
        renderTileInfoUI();
        renderPlayerInfoUI();
        renderTeamInfoUI();
        m_window.EndDrawing();
    }
}

void GraphicalManager::initResourceMap()
{
    m_resource.emplace(Types::ResourceType::FOOD,
        "Source/Graphical/Assets/Resources/food.obj");
    m_resource.emplace(Types::ResourceType::LINEMATE,
        "Source/Graphical/Assets/Resources/linemate.obj");
    m_resource.emplace(Types::ResourceType::DERAUMERE,
        "Source/Graphical/Assets/Resources/deraumere.obj");
    m_resource.emplace(Types::ResourceType::SIBUR,
        "Source/Graphical/Assets/Resources/sibur.obj");
    m_resource.emplace(Types::ResourceType::MENDIANE,
        "Source/Graphical/Assets/Resources/mendiane.obj");
    m_resource.emplace(Types::ResourceType::PHIRAS,
        "Source/Graphical/Assets/Resources/phiras.obj");
    m_resource.emplace(Types::ResourceType::THYSTAME,
        "Source/Graphical/Assets/Resources/thystame.obj");
}
void GraphicalManager::renderMapResources()
{
    for (std::size_t x = 0; x < m_map.getWidth(); ++x) {
        for (std::size_t y = 0; y < m_map.getHeight(); ++y) {
            renderResource(x, y);
        }
    }
}

void GraphicalManager::renderResource(std::size_t x, std::size_t y)
{
    Vector3 position = m_map.at(x, y).getGraphicalPosition();

    for (std::size_t i = 0; i < static_cast<size_t>(Types::ResourceType::COUNT); ++i) {
        if (m_map.at(x, y).getResources()[i] > 0) {
            auto resourceType = static_cast<Types::ResourceType>(i);
            if (i % 2 == 1) {
            m_resource.at(resourceType).Draw({(float)(position.x + ((i * 0.1) + 0.2)),
                position.y, (float)(position.z + -0.65)}, 0.1f, WHITE);
            } else {
                m_resource.at(resourceType).Draw({(float)(position.x + ((i * 0.1) + 0.25)),
                position.y, (float)(position.z + -0.85)}, 0.1f, WHITE);
            }
        }
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
            if (!player.get()->isAlive())
                continue;
            player.get()->update();
            player.get()->draw();
        }
    }
}

void GraphicalManager::CheckMapTileClicked()
{
    std::optional<std::pair<std::size_t, std::size_t>> closestTileCoords = std::nullopt;
    float closestDistance = FLT_MAX;

    Vector2 mousePosition = Raylib::Core::Input::GetMousePosition();
    Ray mouseRay = Raylib::Core::Input::GetMouseRay(mousePosition, m_camera.GetRLCamera());

    for (std::size_t x = 0; x < m_map.getWidth(); ++x) {
        for (std::size_t y = 0; y < m_map.getHeight(); ++y) {
            GraphicalTile &tile = m_map.at(x, y);
            RayCollision collision = tile.m_model.CheckCollisionMeshes(
                mouseRay,
                tile.getGraphicalPosition(),
                TILE_SCALE
            );
            if (collision.hit && collision.distance < closestDistance) {
                closestDistance = collision.distance;
                closestTileCoords = std::make_pair(x, y);
            }
        }
    }
    if (closestTileCoords.has_value()) {
        m_selectedTileCoords = closestTileCoords;
        m_showTileInfo = true;
    } else {
        m_selectedTileCoords = std::nullopt;
        m_showTileInfo = false;
    }
}

void GraphicalManager::renderSelectedTileBorder()
{
    if (!m_selectedTileCoords.has_value())
        return;
    auto [x, y] = m_selectedTileCoords.value();
    const GraphicalTile &selectedTile = m_map.at(x, y);
    Vector3 tilePos = selectedTile.getGraphicalPosition();
    
    selectedTile.m_model.DrawWireframe(tilePos, TILE_SCALE, BLUE);
}

void GraphicalManager::renderSelectedPlayerBorder()
{
    if (!m_showPlayerInfo || m_selectedPlayer == nullptr)
        return;
    Vector3 playerPos = m_selectedPlayer->getGraphicalPosition();   
 
    m_selectedPlayer->m_model.DrawWireframe(playerPos, PLAYER_SCALE, RED);
}

void GraphicalManager::renderTileInfoUI()
{
    if (!m_showTileInfo || !m_selectedTileCoords.has_value())
        return;

    auto [x, y] = m_selectedTileCoords.value();
    const GraphicalTile &selectedTile = m_map.at(x, y);
    int rectX = m_windowInfo.windowWidth - 450;
    int rectY = 20;
    int rectWidth = 440;
    int rectHeight = 360;
    std::string info = getTileInfoText(selectedTile);
    int textY = rectY + 40;
    int lineHeight = 30;

    Raylib::Graphics::Shapes::DrawRectangle(rectX, rectY, rectWidth, rectHeight, {50, 50, 50, 200});
    Raylib::Graphics::Shapes::DrawRectangleLines(rectX, rectY, rectWidth, rectHeight, BLACK);
    Raylib::Graphics::Shapes::DrawText("Tile Informations:\n", rectX + 10, rectY + 10, 22, WHITE);    
    std::istringstream iss(info);
    std::string line;
    while (std::getline(iss, line)) {
        Raylib::Graphics::Shapes::DrawText(line, rectX + 10, textY, 20, WHITE);
        textY += lineHeight;
    }
}

std::string GraphicalManager::getTileInfoText(const GraphicalTile &tile) const
{
    std::ostringstream oss;
    Types::Position pos = tile.getPosition();
    const auto &resources = tile.getResources();
    std::vector<std::string> resourceNames = {
        "Food", "Linemate", "Deraumere", "Sibur", 
        "Mendiane", "Phiras", "Thystame"
    };

    oss << "Position: (" << pos.x << ", " << pos.y << ")\n";
    oss << "Player number: " << tile.getNbPlayers() << std::endl;
    oss << "Resources:\n";
    for (std::size_t i = 0; i < static_cast<size_t>(Types::ResourceType::COUNT); ++i) {
            oss << "  " << resourceNames[i] << ": " << resources[i] << "\n";
    }
    return oss.str();
}

void GraphicalManager::CheckObjectClicked()
{
    if (!Raylib::Core::Input::IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return;
    CheckPlayerClicked();
    if (!m_showPlayerInfo)
        CheckMapTileClicked();
}

void GraphicalManager::CheckPlayerClicked()
{
    Vector2 mousePosition = Raylib::Core::Input::GetMousePosition();
    Ray mouseRay = Raylib::Core::Input::GetMouseRay(mousePosition, m_camera.GetRLCamera());    
    std::shared_ptr<GraphicalPlayer> closestPlayer = nullptr;
    float closestDistance = FLT_MAX;

    for (auto &team : m_teams) {
        for (auto &player : team.second) {
            RayCollision collision = player->m_model.CheckCollisionMeshes(
                mouseRay,
                player->getGraphicalPosition(),
                PLAYER_SCALE
            );
            if (collision.hit && collision.distance < closestDistance) {
                closestDistance = collision.distance;
                closestPlayer = player;
            }
        }
    }
    if (closestPlayer != nullptr) {
        m_selectedPlayer = closestPlayer;
        m_showPlayerInfo = true;        
        Types::Position playerPos = closestPlayer->getPosition();
        m_selectedTileCoords = std::make_pair(playerPos.x, playerPos.y);
        m_showTileInfo = true;
    } else {
        m_selectedPlayer = nullptr;
        m_showPlayerInfo = false;
    }
}

void GraphicalManager::renderPlayerInfoUI()
{
    if (!m_showPlayerInfo || m_selectedPlayer == nullptr)
        return;

    int rectWidth = 400;
    int rectHeight = 530;
    int rectX = 20;
    int rectY = 20;
    std::string info = getPlayerInfoText(*m_selectedPlayer);
    int textY = rectY + 50;
    int lineHeight = 30;

    Raylib::Graphics::Shapes::DrawRectangle(rectX, rectY, rectWidth, rectHeight, {30, 70, 120, 200});
    Raylib::Graphics::Shapes::DrawRectangleLines(rectX, rectY, rectWidth, rectHeight, WHITE);
    Raylib::Graphics::Shapes::DrawText("Player Information:", rectX + 10, rectY + 10, 28, WHITE);
    std::istringstream iss(info);
    std::string line;
    while (std::getline(iss, line)) {
        Raylib::Graphics::Shapes::DrawText(line, rectX + 10, textY, 24, WHITE);
        textY += lineHeight;
    }
}

void GraphicalManager::renderTeamInfoUI()
{
    if (!m_showPlayerInfo || m_selectedPlayer == nullptr)
        return;

    std::string teamName = m_selectedPlayer->getTeamName();
    int rectWidth = 400;
    int rectHeight = 250;
    int rectX = 20;
    int rectY = 560;
    std::string info = getTeamInfoText(teamName);
    int textY = rectY + 50;
    int lineHeight = 30;

    Raylib::Graphics::Shapes::DrawRectangle(rectX, rectY, rectWidth, rectHeight, {120, 70, 30, 200});
    Raylib::Graphics::Shapes::DrawRectangleLines(rectX, rectY, rectWidth, rectHeight, WHITE);    
    Raylib::Graphics::Shapes::DrawText("Team Information:", rectX + 10, rectY + 10, 28, WHITE);    
    std::istringstream iss(info);
    std::string line;
    while (std::getline(iss, line)) {
        Raylib::Graphics::Shapes::DrawText(line, rectX + 10, textY, 24, WHITE);
        textY += lineHeight;
    }
}

std::string GraphicalManager::getPlayerInfoText(const GraphicalPlayer &player) const
{
    std::ostringstream oss;
    Types::Position pos = player.getPosition();
    const auto &inventory = player.getInventory();
    std::vector<std::string> resourceNames = {
        "Food", "Linemate", "Deraumere", "Sibur",
        "Mendiane", "Phiras", "Thystame"
    };

    oss << "ID: " << player.getPlayerId() << "\n";
    oss << "Team: " << player.getTeamName() << "\n";
    oss << "Position: (" << pos.x << ", " << pos.y << ")\n";
    oss << "Level: " << player.getLevel() << "\n";
    oss << "Life: " << player.getLife() << "\n";
    oss << "Status: " << (player.isAlive() ? "Alive" : "Dead") << "\n";    
    std::string orientationStr;
    switch (player.getOrientation()) {
        case Types::Orientation::NORTH: orientationStr = "North"; break;
        case Types::Orientation::SOUTH: orientationStr = "South"; break;
        case Types::Orientation::EAST: orientationStr = "East"; break;
        case Types::Orientation::WEST: orientationStr = "West"; break;
    }
    oss << "Orientation: " << orientationStr << "\n\n";
    oss << "Inventory:\n";
    for (std::size_t i = 0; i < static_cast<size_t>(Types::ResourceType::COUNT); ++i) {
        oss << "  " << resourceNames[i] << ": " << inventory[i] << "\n";
    }
    return oss.str();
}

std::string GraphicalManager::getTeamInfoText(const std::string &teamName) const
{
    uint32_t minLevel = UINT32_MAX;
    uint32_t maxLevel = 0;
    uint32_t aliveCount = 0;
    uint32_t deadCount = 0;
    std::ostringstream oss;
    auto teamIt = m_teams.find(teamName);

    if (teamIt == m_teams.end()) {
        oss << "Team not found!";
        return oss.str();
    }
    const auto &players = teamIt->second;
    if (players.empty()) {
        oss << "No players in team!";
        return oss.str();
    }
    for (const auto &player : players) {
        uint32_t level = player->getLevel();
        minLevel = std::min(minLevel, level);
        maxLevel = std::max(maxLevel, level);
        
        if (player->isAlive()) {
            aliveCount++;
        } else {
            deadCount++;
        }
    }

    oss << "Team: " << teamName << "\n";
    oss << "Total players: " << players.size() << "\n";
    oss << "Players alive: " << aliveCount << "\n";
    oss << "Players dead: " << deadCount << "\n";
    oss << "Min level: " << minLevel << "\n";
    oss << "Max level: " << maxLevel << "\n";
    return oss.str();
}
}
