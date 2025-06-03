/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Material
*/

#include "Raylib/Graphics/Material.hpp"

namespace Raylib {
namespace Graphics {

Material::Material(Color tint) : ownsShader_(false)
{
    material_ = ::LoadMaterialDefault();
    material_.maps[MATERIAL_MAP_DIFFUSE].color = tint;
}

Material::Material(const Texture &diffuseTexture, Color tint)
    : Material(tint)
{
    SetDiffuseTexture(diffuseTexture);
}

Material::~Material()
{
    if (ownsShader_ && material_.shader.id != 0) {
        ::UnloadShader(material_.shader);
    }
}

void Material::SetDiffuseTexture(const Texture &texture)
{
    material_.maps[MATERIAL_MAP_DIFFUSE].texture = texture.GetRLTexture();
}

void Material::RemoveDiffuseTexture()
{
    material_.maps[MATERIAL_MAP_DIFFUSE].texture.id = 0;
    material_.maps[MATERIAL_MAP_DIFFUSE].texture.width = 0;
    material_.maps[MATERIAL_MAP_DIFFUSE].texture.height = 0;;
}

void Material::SetTint(Color tint)
{
    material_.maps[MATERIAL_MAP_DIFFUSE].color = tint;
}

void Material::SetShader(Shader shader)
{
    if (ownsShader_ && material_.shader.id != 0)
        ::UnloadShader(material_.shader);
    material_.shader = shader;
    ownsShader_ = (shader.id != 0);
}

const ::Material &Material::GetRLMaterial() const
{
    return material_;
}

::Material &Material::GetRLMaterial()
{
    return material_;
}
}
}