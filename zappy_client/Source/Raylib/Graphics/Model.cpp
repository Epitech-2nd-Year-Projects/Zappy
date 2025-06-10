/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Model
*/

#include <float.h>
#include "Raylib/Graphics/Model.hpp"

namespace Raylib {
namespace Graphics {

Model::Model(const std::string &filePath)
{
    model_ = ::LoadModel(filePath.c_str());
    if (!IsReady())
        throw ModelException("Failed to load model: " + filePath);
}

Model::Model(const ::Mesh &mesh, const ::Material& material)
{
    model_ = ::LoadModelFromMesh(mesh);
    if (!IsReady())
        throw ModelException("Failed to create model from mesh.");
    if (model_.materialCount > 0)
        model_.materials[0] = material;
}

Model::~Model()
{
    if (IsReady())
        ::UnloadModel(model_);
}

void Model::Draw(Vector3 position, float scale, Color tint) const
{
    ::DrawModel(model_, position, scale, tint);
}

void Model::Draw(Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint) const
{
    ::DrawModelEx(model_, position, rotationAxis, rotationAngle, scale, tint);
}

void Model::SetMaterial(const Material &material, int materialIndex)
{
    if (materialIndex >= 0 && materialIndex < model_.materialCount)
        model_.materials[materialIndex] = material.GetRLMaterial();
}

bool Model::IsReady() const
{
    return model_.meshCount > 0 && model_.meshes != nullptr;
}

::RayCollision Model::CheckCollision(const ::Ray &ray) const
{
    BoundingBox bbox = GetModelBoundingBox(model_);
    return GetRayCollisionBox(ray, bbox);
}

::RayCollision Model::CheckCollisionMesh(const ::Ray &ray) const
{
    RayCollision closestCollision = {};
    closestCollision.hit = false;
    closestCollision.distance = FLT_MAX;

    for (std::size_t i = 0; i < static_cast<std::size_t>(model_.meshCount); ++i) {
        Mesh mesh = model_.meshes[i];
        RayCollision collision = GetRayCollisionMesh(ray, mesh, model_.transform);
        if (collision.hit && collision.distance < closestCollision.distance) {
            closestCollision = collision;
        }
    }
    return closestCollision;
}
}
}
