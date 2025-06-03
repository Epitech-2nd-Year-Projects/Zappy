/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Camera
*/

#pragma once

#include <raylib.h>

namespace Raylib {
namespace Graphics {

class Camera {
public:
    /**
     * @brief Constructs a Camera object with default perspective settings.
     * Default position: (0, 0, 0), target: (0, 0, 0), up: (0, 1, 0), FOV: 45.0, projection: CAMERA_PERSPECTIVE.
     */
    Camera();

    /**
     * @brief Constructs a Camera object with specified initial parameters.
     * @param position The camera's world position.
     * @param target The point in world space the camera is looking at.
     * @param up The up direction for the camera (e.g., {0.0f, 1.0f, 0.0f} for Y-up).
     * @param fovY The field of view in Y direction (in degrees).
     * @param projection The camera projection type (CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC).
     */
    Camera(Vector3 position, Vector3 target, Vector3 up, float fovY, int projection);

    /**
     * @brief Destructor.
     */
    ~Camera() = default;

    /**
     * @brief Starts the 3D drawing mode using this camera.
     * Must be called before drawing any 3D objects.
     */
    void BeginMode3D() const;

    /**
     * @brief Ends the 3D drawing mode.
     * Must be called after drawing all 3D objects.
     */
    void EndMode3D() const;

    /**
     * @brief Updates the camera's position and orientation based on input.
     * This function typically uses Raylib's UpdateCamera internally.
     * @param mode The camera movement mode (e.g., CAMERA_FREE, CAMERA_ORBITAL, etc.).
     */
    void Update(int mode);

    /**
     * @brief Sets the camera's world position.
     * @param position The new position.
     */
    void SetPosition(Vector3 position);

    /**
     * @brief Sets the point in world space the camera is looking at.
     * @param target The new target point.
     */
    void SetTarget(Vector3 target);

    /**
     * @brief Sets the up direction for the camera.
     * @param up The new up vector.
     */
    void SetUp(Vector3 up);

    /**
     * @brief Sets the field of view in Y direction (in degrees).
     * @param fovY The new FOV.
     */
    void SetFovY(float fovY);

    /**
     * @brief Sets the camera projection type.
     * @param projection The new projection type (CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC).
     */
    void SetProjection(int projection);

    /**
     * @brief Gets the current camera's world position.
     * @return The current position vector.
     */
    Vector3 GetPosition() const;

    /**
     * @brief Gets the current camera's target point.
     * @return The current target vector.
     */
    Vector3 GetTarget() const;

    /**
     * @brief Gets the current camera's up direction.
     * @return The current up vector.
     */
    Vector3 GetUp() const;

    /**
     * @brief Gets the current camera's field of view in Y direction.
     * @return The current FOV in degrees.
     */
    float GetFovY() const;

    /**
     * @brief Gets the current camera's projection type.
     * @return The current projection type.
     */
    int GetProjection() const;

    /**
     * @brief Get the underlying Raylib Camera3D structure.
     * Useful for functions that directly interact with Raylib's Camera3D.
     * @return A const reference to the internal Camera3D structure.
     */
    const Camera3D &GetRLCamera() const { return camera_; }

    /**
     * @brief Get a modifiable reference to the underlying Raylib Camera3D structure.
     * Use with caution, as it allows direct modification of Raylib's struct.
     * @return A reference to the internal Camera3D structure.
     */
    Camera3D &GetRLCamera() { return camera_; }

private:
    Camera3D camera_;
};

}
}
