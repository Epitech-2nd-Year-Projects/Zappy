/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Model
*/

#pragma once

#include "Raylib/Graphics/Material.hpp"

namespace Raylib {
namespace Graphics {

class Model {
public:
    /**
     * @brief Constructs a Model by loading it from a specified file path.
     * Raylib automatically loads associated meshes, materials, and textures
     * (e.g., .obj with .mtl, .gltf).
     * @param filePath The path to the model file (e.g., .obj, .gltf, .iqm).
     * @throws std::runtime_error if the model fails to load.
     */
    explicit Model(const std::string &filePath);

    /**
     * @brief Constructs a Model from an existing Raylib Mesh and Material.
     * This constructor is useful for creating models from programmatically generated meshes.
     * The mesh and material themselves are expected to be managed externally.
     * @param mesh The Raylib Mesh structure. A copy of the mesh data will be made internally.
     * @param material The Raylib Material structure to apply to the model.
     * @throws std::runtime_error if the model creation from mesh fails.
     */
    Model(const ::Mesh &mesh, const ::Material& material);

    /**
     * @brief Destructor. Unloads the Raylib Model resource if it was loaded by this instance.
     */
    ~Model();

    Model(const Model&) = delete;
    Model &operator=(const Model&) = delete;

    /**
     * @brief Draws the model at a specific position with a uniform scale and tint.
     * @param position The world position to draw the model.
     * @param scale The uniform scaling factor.
     * @param tint The color to tint the model (defaults to WHITE).
     */
    void Draw(Vector3 position, float scale, Color tint = WHITE) const;

    /**
     * @brief Draws the model with detailed transformations (position, rotation, scale).
     * @param position The world position to draw the model.
     * @param rotationAxis The axis around which to rotate the model.
     * @param rotationAngle The rotation angle in degrees.
     * @param scale The scaling vector (X, Y, Z).
     * @param tint The color to tint the model (defaults to WHITE).
     */
    void Draw(Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint = WHITE) const;

    /**
     * @brief Sets the material for a specific mesh part of the model.
     * Most simple models have only one material at index 0.
     * The material object itself is expected to be managed externally.
     * @param material A const reference to the Material object to apply.
     * @param materialIndex The index of the material to change (defaults to 0).
     */
    void SetMaterial(const Material &material, int materialIndex = 0);

    /**
     * @brief Checks if the model has been successfully loaded and is ready for use.
     * A model is considered ready if it contains at least one mesh.
     * @return true if the model is ready, false otherwise.
     */
    bool IsReady() const;

    /**
     * @brief Gets a const reference to the underlying Raylib Model structure.
     * @return A const reference to Model.
     */
    const ::Model &GetRLModel() const { return model_; }

    /**
     * @brief Gets a mutable reference to the underlying Raylib Model structure.
     * Use with caution.
     * @return A mutable reference to Model.
     */
    ::Model &GetRLModel() { return model_; }
private:
    ::Model model_;

    class ModelException : public std::exception {
    public:
        /**
         * @brief Constructs a WindowException with a specified error message.
         * @param message A string describing the error.
         */
        ModelException(const std::string &message) : message_(message) {}

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
}
