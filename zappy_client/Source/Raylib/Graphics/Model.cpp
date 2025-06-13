/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Model
*/

#include <float.h>
#include "Raylib/Graphics/Model.hpp"
#include <raymath.h>

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

::RayCollision Model::CheckCollisionBoundingBox(const ::Ray &ray, Vector3 position) const
{
    BoundingBox localBbox = GetModelBoundingBox(model_);
    BoundingBox worldBbox = {
        .min = { localBbox.min.x + position.x, localBbox.min.y + position.y, localBbox.min.z + position.z },
        .max = { localBbox.max.x + position.x, localBbox.max.y + position.y, localBbox.max.z + position.z }
    };
    return GetRayCollisionBox(ray, worldBbox);
}
void Model::DrawWireframe(Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint) const
{
    ::DrawModelWiresEx(model_, position, rotationAxis, rotationAngle, scale, tint);
}

void Model::DrawWireframe(Vector3 position, float scale, Color tint) const
{
    DrawWireframe(position, {0.0f, 1.0f, 0.0f}, 0.0f, {scale, scale, scale}, tint);
}

::RayCollision Model::CheckCollisionMeshes(const ::Ray &ray, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale) const
{
    RayCollision closestCollision = {};
    closestCollision.hit = false;
    closestCollision.distance = FLT_MAX;

    Matrix transform = ::MatrixMultiply(
        ::MatrixMultiply(
            ::MatrixScale(scale.x, scale.y, scale.z),
            ::MatrixRotate(rotationAxis, rotationAngle * DEG2RAD)
        ),
        ::MatrixTranslate(position.x, position.y, position.z)
    );
    for (std::size_t i = 0; i < static_cast<std::size_t>(model_.meshCount); ++i) {
        RayCollision collision = GetRayCollisionMesh(ray, model_.meshes[i], transform);
        if (collision.hit && collision.distance < closestCollision.distance) {
            closestCollision = collision;
        }
    }
    return closestCollision;
}

::RayCollision Model::CheckCollisionMeshes(const ::Ray &ray, Vector3 position, float scale) const
{
    return CheckCollisionMeshes(ray, position, {0.0f, 1.0f, 0.0f}, 0.0f, {scale, scale, scale});
}
}
}
