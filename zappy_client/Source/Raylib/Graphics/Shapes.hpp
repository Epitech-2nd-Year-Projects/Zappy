/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Shapes
*/

#pragma once

#include "Raylib/Graphics/Texture.hpp"
#include "Raylib/Graphics/Material.hpp"

namespace Raylib {
namespace Graphics {

class Shapes {
public:
    Shapes() = delete;
    Shapes(const Shapes &) = delete;
    Shapes &operator=(const Shapes &) = delete;

    /**
     * @brief Draws a rectangle.
     * @param x X position.
     * @param y Y position.
     * @param width Width.
     * @param height Height.
     * @param color The color.
     */
    static void DrawRectangle(int x, int y, int width, int height, Color color);

    /**
     * @brief Draws a rectangle with outline.
     * @param x X position.
     * @param y Y position.
     * @param width Width.
     * @param height Height.
     * @param color The color.
     */
    static void DrawRectangleLines(int x, int y, int width, int height, Color color);
    
    /**
     * @brief Draws a circle.
     * @param centerX Center X position.
     * @param centerY Center Y position.
     * @param radius Radius.
     * @param color The color.
     */
    static void DrawCircle(int centerX, int centerY, float radius, Color color);

    /**
     * @brief Draws text.
     * @param text The string to draw.
     * @param posX X position.
     * @param posY Y position.
     * @param fontSize Font size.
     * @param color The color.
     */
    static void DrawText(const std::string &text, int posX, int posY, int fontSize, Color color);
    
    /**
     * @brief Draws text with custom font (if loaded).
     * @param font The Raylib Font structure.
     * @param text The string to draw.
     * @param position Top-left position.
     * @param fontSize Font size.
     * @param spacing Character spacing.
     * @param tint The color.
     */
    static void DrawTextEx(Font font, const std::string &text, Vector2 position, float fontSize, float spacing, Color tint);

    /**
     * @brief Draws a 3D grid.
     * @param slices Number of slices for the grid.
     * @param spacing Spacing between lines.
     */
    static void DrawGrid(int slices, float spacing);

    /**
     * @brief Draws a cube.
     * @param position Center position.
     * @param width Width.
     * @param height Height.
     * @param length Length.
     * @param color The color.
     */
    static void DrawCube(Vector3 position, float width, float height, float length, Color color);

    /**
     * @brief Draws a cube outline.
     * @param position Center position.
     * @param width Width.
     * @param height Height.
     * @param length Length.
     * @param color The color.
     */
    static void DrawCubeWires(Vector3 position, float width, float height, float length, Color color);

    /**
     * @brief Draws a textured cube using a texture wrapper.
     * This method generates and unloads the cube geometry for each call.
     * For better performance when drawing many textured cubes, consider using Raylib::Graphics::Model directly
     * with a pre-loaded cube model.
     * @param position Center position.
     * @param width Width.
     * @param height Height.
     * @param length Length.
     * @param texture The Texture object to apply.
     * @param tint The color to tint the texture (defaults to WHITE).
     */
    static void DrawTexturedCube(Vector3 position, float width, float height, float length, const Texture &texture, Color tint = WHITE);

    /**
     * @brief Draws a textured cube using a material wrapper.
     * This method generates and unloads the cube geometry for each call.
     * For better performance when drawing many textured cubes, consider using Raylib::Graphics::Model directly
     * with a pre-loaded cube model.
     * @param position Center position.
     * @param width Width.
     * @param height Height.
     * @param length Length.
     * @param material The Material object to apply.
     */
    static void DrawTexturedCube(Vector3 position, float width, float height, float length, const Material &material);

    /**
     * @brief Draws a sphere.
     * @param centerPos Center position.
     * @param radius Radius.
     * @param color The color.
     */
    static void DrawSphere(Vector3 centerPos, float radius, Color color);

    /**
     * @brief Draws a textured sphere using a texture wrapper.
     * This method generates and unloads the sphere geometry for each call.
     * For better performance when drawing many textured spheres, consider using Raylib::Graphics::Model directly
     * with a pre-loaded sphere model.
     * @param centerPos Center position.
     * @param radius Radius.
     * @param texture The Texture object to apply.
     * @param tint The color to tint the texture (defaults to WHITE).
     */
    static void DrawTexturedSphere(Vector3 centerPos, float radius, const Texture &texture, Color tint = WHITE);

    /**
     * @brief Draws a textured sphere using a material wrapper.
     * This method generates and unloads the sphere geometry for each call.
     * For better performance when drawing many textured spheres, consider using Raylib::Graphics::Model directly
     * with a pre-loaded sphere model.
     * @param centerPos Center position.
     * @param radius Radius.
     * @param material The Material object to apply.
     */
    static void DrawTexturedSphere(Vector3 centerPos, float radius, const Material &material);

    /**
     * @brief Draws a plane (flat rectangle) in 3D space.
     * @param centerPos The center position of the plane.
     * @param size The size of the plane along X and Z axes (Y is ignored, plane is on XZ).
     * @param color The color of the plane.
     */
    static void DrawPlane(Vector3 centerPos, Vector2 size, Color color);

    /**
     * @brief Draws a textured plane (flat rectangle) in 3D space using a texture.
     * This method generates and unloads the plane geometry for each call.
     * @param centerPos The center position of the plane.
     * @param size The size of the plane along X and Z axes.
     * @param texture The Texture object to apply.
     * @param tint The color to tint the texture (defaults to WHITE).
     */
    static void DrawTexturedPlane(Vector3 centerPos, Vector2 size, const Texture &texture, Color tint = WHITE);

    /**
     * @brief Draws a textured plane (flat rectangle) in 3D space using a material.
     * This method generates and unloads the plane geometry for each call.
     * @param centerPos The center position of the plane.
     * @param size The size of the plane along X and Z axes.
     * @param material The Material object to apply.
     */
    static void DrawTexturedPlane(Vector3 centerPos, Vector2 size, const Material &material);
};

}
}
