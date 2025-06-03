/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Input
*/

#pragma once

#include <raylib.h>

namespace Raylib {
namespace Core {

class Input {
public:
Input() = delete;
/**
 * @brief Checks if a specific key has been pressed once.
 * @param key The key code (e.g., KEY_SPACE, KEY_W).
 * @return true if the key was pressed in the current frame, false otherwise.
 */
static bool IsKeyPressed(int key);
/**
 * @brief Checks if a specific key is currently being held down.
 * @param key The key code.
 * @return true if the key is down, false otherwise.
 */
static bool IsKeyDown(int key);
/**
 * @brief Checks if a specific key has been released once.
 * @param key The key code.
 * @return true if the key was released in the current frame, false otherwise.
 */
static bool IsKeyReleased(int key);
/**
 * @brief Checks if a specific key is NOT being held down.
 * @param key The key code.
 * @return true if the key is up, false otherwise.
 */
static bool IsKeyUp(int key);

/**
 * @brief Gets the key pressed in the current frame.
 * @return The key code, or 0 if no key was pressed.
 */
static int GetKeyPressed();

/**
 * @brief Checks if a specific mouse button has been pressed once.
 * @param button The mouse button code (e.g., MOUSE_BUTTON_LEFT, MOUSE_BUTTON_RIGHT).
 * @return true if the button was pressed in the current frame, false otherwise.
 */
static bool IsMouseButtonPressed(int button);
/**
 * @brief Checks if a specific mouse button is currently being held down.
 * @param button The mouse button code.
 * @return true if the button is down, false otherwise.
 */
static bool IsMouseButtonDown(int button);
/**
 * @brief Checks if a specific mouse button has been released once.
 * @param button The mouse button code.
 * @return true if the button was released in the current frame, false otherwise.
 */
static bool IsMouseButtonReleased(int button);
/**
 * @brief Checks if a specific mouse button is NOT being held down.
 * @param button The mouse button code.
 * @return true if the button is up, false otherwise.
 */
static bool IsMouseButtonUp(int button);
/**
 * @brief Gets the current mouse cursor position.
 * @return A Vector2 representing the (x, y) coordinates of the mouse cursor.
 */
static Vector2 GetMousePosition();
/**
 * @brief Gets the mouse delta, the movement of the mouse cursor since the last frame.
 * @return A Vector2 representing the mouse delta.
 */
static Vector2 GetMouseDelta();
/**
 * @brief Gets the mouse wheel movement for the current frame.
 * @return The mouse wheel movement (positive for scroll up, negative for scroll down).
 */
static float GetMouseWheelMove();
/**
 * @brief Sets the current mouse cursor.
 * @param cursor The desired cursor type (e.g., MOUSE_CURSOR_ARROW, MOUSE_CURSOR_IBEAM).
 */
static void SetMouseCursor(int cursor);
// --- Raylib-specific 3D picking functions (requires a camera) ---
/**
 * @brief Gets a picking ray from the camera position, projected from the mouse.
 * Useful for 3D object selection.
 * @param mousePosition The 2D mouse position.
 * @param camera The 3D camera from which to cast the ray.
 * @return A Ray structure.
 */
static Ray GetMouseRay(Vector2 mousePosition, Camera3D camera);
};

}
}
