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

void GraphicalManager::runRender()
{
    render();
}

}
