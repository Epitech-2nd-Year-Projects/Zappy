/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Materail
*/

#pragma once

#include "Raylib/Graphics/Texture.hpp"

namespace Raylib {
namespace Graphics {

class Material {
public:
    /**
     * @brief Constructs a Material with a default diffuse color and no texture.
     * @param tint The diffuse color (defaults to WHITE).
     */
    explicit Material(Color tint = WHITE);

    /**
     * @brief Constructs a Material with a specified diffuse texture and tint color.
     * The texture must be managed externally (e.g., by an AssetManager).
     * @param diffuseTexture A const reference to the Texture object to use as the diffuse map.
     * @param tint The diffuse color (defaults to WHITE).
     */
    Material(const Texture& diffuseTexture, Color tint = WHITE);

    /**
     * @brief Destructor. Unloads any custom shaders associated with the material.
     * Note: Default materials don't require explicit unloading of the Material structure itself.
     */
    ~Material();

    /**
     * @brief Sets the diffuse texture (the main color texture) for this material.
     * The provided Texture object must be managed externally.
     * @param texture A const reference to the Texture object.
     */
    void SetDiffuseTexture(const Texture& texture);
    
    /**
     * @brief Removes the diffuse texture from this material.
     * The material will then only use its diffuse color.
     */
    void RemoveDiffuseTexture();

    /**
     * @brief Sets the diffuse color (tint) for this material.
     * @param tint The desired tint color.
     */
    void SetTint(Color tint);

    /**
     * @brief Sets a custom shader for this material.
     * The Shader object must be managed externally.
     * @param shader The Raylib Shader structure.
     */
    void SetShader(Shader shader); // Using Raylib's Shader struct directly

    /**
     * @brief Gets a const reference to the underlying Raylib Material structure.
     * @return A const reference to Material.
     */
    const ::Material& GetRLMaterial() const;

    /**
     * @brief Gets a mutable reference to the underlying Raylib Material structure.
     * Use with caution.
     * @return A mutable reference to Material.
     */
    ::Material& GetRLMaterial();

private:
    ::Material material_;
    bool owns_shader_;
};

}
}
