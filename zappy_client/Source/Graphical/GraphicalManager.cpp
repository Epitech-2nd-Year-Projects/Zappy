/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** GraphicalManager
*/

#include "GraphicalManager.hpp"

namespace GUI {

GraphicalManager::GraphicalManager()
: m_windowName("Zappy"),
  m_windowWidth(DEFAULT_WINDOW_WIDTH),
  m_windowHeight(DEFAULT_WINDOW_HEIGHT),
  m_window(m_windowWidth, m_windowHeight, m_windowName)
{
    m_camera.Update(CAMERA_FREE);
}

GraphicalManager::~GraphicalManager()
{
}

}
