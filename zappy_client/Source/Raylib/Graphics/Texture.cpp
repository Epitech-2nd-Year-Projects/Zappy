/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Texture
*/

#include "Raylib/Graphics/Texture.hpp"

namespace Raylib {
namespace Graphics {

Texture::Texture(const std::string& filePath)
{
    texture_ = ::LoadTexture(filePath.c_str());
    if (!IsReady())
        throw TextureException("Failed to load texture: " + filePath);
}

Texture::~Texture() {
    if (IsReady()) {
        ::UnloadTexture(texture_);
    }
}

const Texture2D &Texture::GetRLTexture() const
{
    return texture_;
}

Texture2D &Texture::GetRLTexture()
{
    return texture_;
}

bool Texture::IsReady() const
{
    return texture_.id != 0;
}

int Texture::GetWidth() const
{
    return texture_.width;
}

int Texture::GetHeight() const
{
    return texture_.height;
}

}
}