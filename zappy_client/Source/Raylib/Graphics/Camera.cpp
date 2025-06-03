/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Camera
*/

#include "Raylib/Graphics/Camera.hpp"

namespace Raylib {
namespace Graphics {

Camera::Camera()
{
    camera_.position = {0.0f, 0.0f, 0.0f};
    camera_.target = {0.0f, 0.0f, 0.0f};
    camera_.up = {0.0f, 1.0f, 0.0f};
    camera_.fovy = 45.0f;
    camera_.projection = CAMERA_PERSPECTIVE;
}

Camera::Camera(Vector3 position, Vector3 target, Vector3 up, float fovY, int projection)
{
    camera_.position = position;
    camera_.target = target;
    camera_.up = up;
    camera_.fovy = fovY;
    camera_.projection = projection;
}

void Camera::BeginMode3D() const
{
    ::BeginMode3D(camera_);
}

void Camera::EndMode3D() const
{
    ::EndMode3D();
}

void Camera::Update(int mode)
{
    ::UpdateCamera(&camera_, mode);
}

void Camera::SetPosition(Vector3 position)
{
    camera_.position = position;
}

void Camera::SetTarget(Vector3 target)
{
    camera_.target = target;
}

void Camera::SetUp(Vector3 up)
{
    camera_.up = up;
}

void Camera::SetFovY(float fovY)
{
    camera_.fovy = fovY;
}

void Camera::SetProjection(int projection)
{
    camera_.projection = projection;
}

Vector3 Camera::GetPosition() const
{
    return camera_.position;
}

Vector3 Camera::GetTarget() const
{
    return camera_.target;
}

Vector3 Camera::GetUp() const
{
    return camera_.up;
}

float Camera::GetFovY() const
{
    return camera_.fovy;
}

int Camera::GetProjection() const
{
    return camera_.projection;
}
}
}
