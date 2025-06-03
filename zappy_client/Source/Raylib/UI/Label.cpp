/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Label
*/

#include "Raylib/UI/Label.hpp"

namespace Raylib {
namespace UI {

Label::Label(Rectangle bounds, const std::string &text, int fontSize, Color color, bool isVisible)
    : Widget(bounds, isVisible),
      text_(text),
      fontSize_(fontSize),
      color_(color),
      font_(Font{}),
      spacing_(0.0f),
      useCustomFont_(false)
{
}

Label::Label(Rectangle bounds, const std::string &text, const Font &font, float fontSize, float spacing, Color color, bool isVisible)
    : Widget(bounds, isVisible),
      text_(text),
      fontSize_(fontSize),
      color_(color),
      font_(font),
      spacing_(spacing),
      useCustomFont_(true)
{
}

void Label::Update([[maybe_unused]] float deltaTime)
{
}

void Label::Draw()
{
    if (!isVisible_)
        return;
    if (useCustomFont_) {
        Graphics::Shapes::DrawTextEx(font_, text_.c_str(), {bounds_.x, bounds_.y}, (float)fontSize_, spacing_, color_);
    } else {
        Graphics::Shapes::DrawText(text_.c_str(), (int)bounds_.x, (int)bounds_.y, fontSize_, color_);
    }
}

void Label::SetText(const std::string &newText)
{
    text_ = newText;
}

void Label::SetColor(Color newColor)
{
    color_ = newColor;
}

void Label::SetFontSize(int newFontSize)
{
    fontSize_ = newFontSize;
}

void Label::SetFont(const Font &newFont)
{
    font_ = newFont;
    useCustomFont_ = true;
}

void Label::SetSpacing(float newSpacing)
{
    spacing_ = newSpacing;
}

}
}