/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Input
*/

#include "Raylib/Core/Input.hpp"

namespace Raylib {
namespace Core {

bool Input::IsKeyPressed(int key)
{
    return ::IsKeyPressed(key);
}

bool Input::IsKeyDown(int key)
{
    return ::IsKeyDown(key);
}

bool Input::IsKeyReleased(int key)
{
    return ::IsKeyReleased(key);
}

bool Input::IsKeyUp(int key)
{
    return ::IsKeyUp(key);
}

int Input::GetKeyPressed()
{
    return ::GetKeyPressed();
}

bool Input::IsMouseButtonPressed(int button)
{
    return ::IsMouseButtonPressed(button);
}

bool Input::IsMouseButtonDown(int button)
{
    return ::IsMouseButtonDown(button);
}

bool Input::IsMouseButtonReleased(int button)
{
    return ::IsMouseButtonReleased(button);
}

bool Input::IsMouseButtonUp(int button)
{
    return ::IsMouseButtonUp(button);
}

Vector2 Input::GetMousePosition()
{
    return ::GetMousePosition();
}

Vector2 Input::GetMouseDelta()
{
    return ::GetMouseDelta();
}

float Input::GetMouseWheelMove()
{
    return ::GetMouseWheelMove();
}

void Input::SetMouseCursor(int cursor)
{
    ::SetMouseCursor(cursor);
}

Ray Input::GetMouseRay(Vector2 mousePosition, Camera3D camera)
{
    return ::GetMouseRay(mousePosition, camera);
}
}
}