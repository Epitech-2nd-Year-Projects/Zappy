/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Shapes
*/

#include "Raylib/Graphics/Shapes.hpp"

namespace Raylib {
namespace Graphics {

void Shapes::DrawRectangle(int x, int y, int width, int height, Color color)
{
    ::DrawRectangle(x, y, width, height, color);
}

void Shapes::DrawRectangleLines(int x, int y, int width, int height, Color color)
{
    ::DrawRectangleLines(x, y, width, height, color);
}

void Shapes::DrawCircle(int centerX, int centerY, float radius, Color color)
{
    ::DrawCircle(centerX, centerY, radius, color);
}

void Shapes::DrawText(const std::string &text, int posX, int posY, int fontSize, Color color)
{
    ::DrawText(text.c_str(), posX, posY, fontSize, color);
}

void Shapes::DrawTextEx(Font font, const std::string &text, Vector2 position, float fontSize, float spacing, Color tint)
{
    ::DrawTextEx(font, text.c_str(), position, fontSize, spacing, tint);
}

void Shapes::DrawGrid(int slices, float spacing) {
    ::DrawGrid(slices, spacing);
}

void Shapes::DrawCube(Vector3 position, float width, float height, float length, Color color)
{
    ::DrawCube(position, width, height, length, color);
}

void Shapes::DrawCubeWires(Vector3 position, float width, float height, float length, Color color)
{
    ::DrawCubeWires(position, width, height, length, color);
}

void Shapes::DrawTexturedCube(Vector3 position, float width, float height, float length, const Texture &texture, Color tint)
{
    ::Mesh cubeMesh = ::GenMeshCube(1.0f, 1.0f, 1.0f);
    ::Model cubeModel = ::LoadModelFromMesh(cubeMesh);
    ::Material tempMaterial = ::LoadMaterialDefault();
    tempMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = texture.GetRLTexture();
    tempMaterial.maps[MATERIAL_MAP_DIFFUSE].color = tint;
    cubeModel.materials[0] = tempMaterial;

    ::DrawModelEx(cubeModel, position, (Vector3){0.0f, 1.0f, 0.0f}, 0.0f, (Vector3){width, height, length}, WHITE);
    ::UnloadModel(cubeModel);
    ::UnloadMesh(cubeMesh);
}

void Shapes::DrawTexturedCube(Vector3 position, float width, float height, float length, const Material &material)
{
    ::Mesh cubeMesh = ::GenMeshCube(1.0f, 1.0f, 1.0f);
    ::Model cubeModel = ::LoadModelFromMesh(cubeMesh);
    cubeModel.materials[0] = material.GetRLMaterial();

    ::DrawModelEx(cubeModel, position, (Vector3){0.0f, 1.0f, 0.0f}, 0.0f, (Vector3){width, height, length}, WHITE);
    ::UnloadModel(cubeModel);
    ::UnloadMesh(cubeMesh);
}

void Shapes::DrawSphere(Vector3 centerPos, float radius, Color color) {
    ::DrawSphere(centerPos, radius, color);
}

void Shapes::DrawTexturedSphere(Vector3 centerPos, float radius, const Texture &texture, Color tint) {
    ::Mesh sphereMesh = ::GenMeshSphere(radius, 16, 16);
    ::Model sphereModel = ::LoadModelFromMesh(sphereMesh);

    ::Material tempMaterial = ::LoadMaterialDefault();
    tempMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = texture.GetRLTexture();
    tempMaterial.maps[MATERIAL_MAP_DIFFUSE].color = tint;
    sphereModel.materials[0] = tempMaterial;

    ::DrawModel(sphereModel, centerPos, 1.0f, WHITE);

    ::UnloadModel(sphereModel);
    ::UnloadMesh(sphereMesh);
}

void Shapes::DrawTexturedSphere(Vector3 centerPos, float radius, const Material &material) {
    ::Mesh sphereMesh = ::GenMeshSphere(radius, 16, 16);
    ::Model sphereModel = ::LoadModelFromMesh(sphereMesh);
    
    sphereModel.materials[0] = material.GetRLMaterial();

    ::DrawModel(sphereModel, centerPos, 1.0f, WHITE);

    ::UnloadModel(sphereModel);
    ::UnloadMesh(sphereMesh);
}

void Shapes::DrawPlane(Vector3 centerPos, Vector2 size, Color color)
{
    ::DrawPlane(centerPos, (Vector2){size.x, size.y}, color);
}

void Shapes::DrawTexturedPlane(Vector3 centerPos, Vector2 size, const Texture &texture, Color tint)
{
    ::Mesh planeMesh = ::GenMeshPlane(size.x, size.y, 1, 1);
    ::Model planeModel = ::LoadModelFromMesh(planeMesh);
    ::Material tempMaterial = ::LoadMaterialDefault();
    tempMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = texture.GetRLTexture();
    tempMaterial.maps[MATERIAL_MAP_DIFFUSE].color = tint;
    planeModel.materials[0] = tempMaterial;

    ::DrawModel(planeModel, centerPos, 1.0f, WHITE);
    ::UnloadModel(planeModel);
    ::UnloadMesh(planeMesh);
}

void Shapes::DrawTexturedPlane(Vector3 centerPos, Vector2 size, const Material &material)
{
    ::Mesh planeMesh = ::GenMeshPlane(size.x, size.y, 1, 1);
    ::Model planeModel = ::LoadModelFromMesh(planeMesh);
    planeModel.materials[0] = material.GetRLMaterial();

    ::DrawModel(planeModel, centerPos, 1.0f, WHITE);
    ::UnloadModel(planeModel);
    ::UnloadMesh(planeMesh);
}

}
}
