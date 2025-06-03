/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Window
*/

#include "Raylib/Core/Window.hpp"

namespace Raylib {
namespace Core {


Window::Window(int width, int height, const std::string &title, int targetFps)
    : width_(width), height_(height), title_(title), is_window_initialized_(false)
{
    InitWindow(width_, height_, title.c_str());

    if (!IsWindowReady()) {
        throw WindowException("Failed to initialize Raylib window.");
    }
    SetTargetFPS(targetFps);
    is_window_initialized_ = true;
}

Window::~Window()
{
    if (is_window_initialized_) {
        CloseWindow();
        is_window_initialized_ = false;
    }
}

bool Window::ShouldClose() const
{
    return WindowShouldClose();
}

void Window::BeginDrawing()
{
    ::BeginDrawing();
}

void Window::EndDrawing()
{
    ::EndDrawing();
}

void Window::ClearBackground(Color color)
{
    ::ClearBackground(color);
}

void Window::SetTargetFPS(int fps)
{
    ::SetTargetFPS(fps);
}

int Window::GetWidth() const
{
    return GetScreenWidth();
}

int Window::GetHeight() const
{
    return GetScreenHeight();
}

}
}