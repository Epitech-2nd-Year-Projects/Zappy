/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Widget
*/

#pragma once

#include <raylib.h>

namespace Raylib {
namespace UI {

class Widget {
public:
    /**
     * @brief Constructs a Widget.
     * @param bounds Rectangle defining the widget's position (x, y) and size (width, height).
     * @param isVisible Initial visibility state of the widget.
     */
    explicit Widget(Rectangle bounds, bool isVisible = true);

    /**
     * @brief Virtual destructor for polymorphic destruction.
     * Ensures proper cleanup of derived classes.
     */
    virtual ~Widget() = default;

    Widget(const Widget&) = delete;
    Widget &operator=(const Widget&) = delete;

    /**
     * @brief Updates the widget's state based on time and input.
     * This is a pure virtual function that must be implemented by derived classes.
     * @param deltaTime The time elapsed since the last frame, in seconds.
     */
    virtual void Update(float deltaTime) = 0;

    /**
     * @brief Draws the widget on the screen.
     * This is a pure virtual function that must be implemented by derived classes.
     */
    virtual void Draw() = 0;

    /**
     * @brief Checks if a given point is within the widget's bounds.
     * Useful for mouse interaction.
     * @param point The point to check (e.g., mouse position).
     * @return true if the point is within bounds, false otherwise.
     */
    bool IsPointInside(Vector2 point) const;

    /**
     * @brief Sets the visibility of the widget.
     * @param visible The new visibility state.
     */
    void SetVisible(bool visible);

    /**
     * @brief Checks if the widget is currently visible.
     * @return true if visible, false otherwise.
     */
    bool IsVisible() const;

    /**
     * @brief Sets the position of the widget.
     * @param x The new X coordinate.
     * @param y The new Y coordinate.
     */
    void SetPosition(float x, float y);

    /**
     * @brief Sets the size of the widget.
     * @param width The new width.
     * @param height The new height.
     */
    void SetSize(float width, float height);

    /**
     * @brief Gets the current bounds (position and size) of the widget.
     * @return The widget's Rectangle bounds.
     */
    Rectangle GetBounds() const;

protected:
    Rectangle bounds_;
    bool isVisible_;
};
}
}
