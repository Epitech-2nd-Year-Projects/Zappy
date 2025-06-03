/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Window
*/

#pragma once

#include <string>
#include <stdexcept>
#include <raylib.h>

namespace Raylib {
namespace Core {

class Window {
public:
    /**
     * @brief Constructor for the window. Initializes the Raylib context.
     * @param width The width of the window in pixels.
     * @param height The height of the window in pixels.
     * @param title The title of the window.
     * @param targetFps The target frame rate (defaults to 60 FPS).
     * @throws std::runtime_error if Raylib initialization fails.
     */
    Window(int width, int height, const std::string &title, int targetFps = 60);

    /**
     * @brief Destructor for the window. Closes the Raylib context and frees resources.
     */
    ~Window();

    /**
     * @brief Checks if the window should close (e.g., user clicks the close button).
     * @return true if the window should close, false otherwise.
     */
    bool ShouldClose() const;

    /**
     * @brief Starts the drawing mode for the current frame.
     * This function must be called once per frame, before any drawing operations.
     */
    void BeginDrawing();

    /**
     * @brief Ends the drawing mode for the current frame and swaps buffers.
     * This function must be called once per frame, after all drawing operations.
     */
    void EndDrawing();

    /**
     * @brief Clears the background of the window with the specified color.
     * @param color The color to use for the background.
     */
    void ClearBackground(Color color);

    /**
     * @brief Sets the target frame rate for the window.
     * @param fps The target frame rate in frames per second.
     */
    void SetTargetFPS(int fps);

    /**
     * @brief Gets the current width of the window.
     * @return The width of the window in pixels.
     */
    int GetWidth() const;

    /**
     * @brief Gets the current height of the window.
     * @return The height of the window in pixels.
     */
    int GetHeight() const;

/**
 * @brief Custom exception class for errors related to Raylib window operations.
 * This exception is thrown when the window cannot be initialized or if a critical
 * window-related error occurs.
 */
class WindowException : public std::exception {
public:
    /**
     * @brief Constructs a WindowException with a specified error message.
     * @param message A string describing the error.
     */
    WindowException(const std::string &message) : message_(message) {}

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

private:

    int width_;
    int height_;
    std::string title_;
    bool is_window_initialized_;
};

} // namespace Core
} // namespace Raylib
