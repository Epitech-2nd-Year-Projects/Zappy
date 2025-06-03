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
    : bounds_(bounds), isVisible_(isVisible)
{
}

bool Widget::IsPointInside(Vector2 point) const
{
    return ::CheckCollisionPointRec(point, bounds_);
}

void Widget::SetVisible(bool visible)
{
    isVisible_ = visible;
}

bool Widget::IsVisible() const
{
    return isVisible_;
}

void Widget::SetPosition(float x, float y)
{
    bounds_.x = x;
    bounds_.y = y;
}

void Widget::SetSize(float width, float height)
{
    bounds_.width = width;
    bounds_.height = height;
}

Rectangle Widget::GetBounds() const
{
    return bounds_;
}

}
}