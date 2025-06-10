/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** GraphicalManager
*/

#pragma once

#include <cstdio>
#include <string>
#include "Raylib/Core/Window.hpp"
#include "Raylib/Graphics/Camera.hpp"
#include "Graphical/Types/GraphicalTypes.hpp"
#include "EventManager/EventBus.hpp"
#include "EventManager/EventType.hpp"
#include "Graphical/Entity/GraphicalTile.hpp"
#include "Graphical/Utils/Map.hpp"


namespace GUI {

    constexpr std::size_t DEFAULT_WINDOW_WIDTH = 1920;
    constexpr std::size_t DEFAULT_WINDOW_HEIGHT = 1080;

class GraphicalManager {
public:
    GraphicalManager(EventManager::EventBus &eventBus);
    ~GraphicalManager();

    void runRender();

private:
    EventManager::EventBus m_eventBus;
    WindowInformation m_windowInfo;
    Raylib::Core::Window m_window;
    Raylib::Graphics::Camera m_camera;

    Map m_map;

    void render();
    void subscribeToEvents();
    void subscribeToMapEvents();
    void initMap(std::size_t width, std::size_t height);
    void addMapRessources(const EventManager::MapContentEvent &mapContent);

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
