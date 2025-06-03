/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Widget
*/

#include "Raylib/UI/Widget.hpp"

namespace Raylib {
namespace UI {

Widget::Widget(Rectangle bounds, bool isVisible)
    : bounds(bounds), isVisible(isVisible)
{
}

bool Widget::IsPointInside(Vector2 point) const
{
    return ::CheckCollisionPointRec(point, bounds);
}

void Widget::SetVisible(bool visible)
{
    isVisible = visible;
}

bool Widget::IsVisible() const
{
    return isVisible;
}

void Widget::SetPosition(float x, float y)
{
    bounds.x = x;
    bounds.y = y;
}

void Widget::SetSize(float width, float height)
{
    bounds.width = width;
    bounds.height = height;
}

Rectangle Widget::GetBounds() const
{
    return bounds;
}

}
}