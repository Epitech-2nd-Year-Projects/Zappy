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

namespace GUI {

    constexpr std::size_t DEFAULT_WINDOW_WIDTH = 1920;
    constexpr std::size_t DEFAULT_WINDOW_HEIGHT = 1080;

class GraphicalManager {
public:
    GraphicalManager();
    ~GraphicalManager();

    void runRender();

private:
    std::string m_windowName;
    std::size_t m_windowWidth;
    std::size_t m_windowHeight;
    Raylib::Core::Window m_window;
    Raylib::Graphics::Camera m_camera;

    void render();

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
