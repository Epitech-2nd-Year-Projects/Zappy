/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Button
*/

#include "Raylib/UI/Button.hpp"

namespace Raylib {
namespace UI {

Button::Button(Rectangle bounds, const std::string &text, int fontSize,
               Color normalColor, Color hoveredColor, Color pressedColor, Color textColor,
               bool isVisible)
    : Widget(bounds, isVisible),
      text_(text),
      fontSize_(fontSize),
      spacing_(0.0f),
      font_(Font{}),
      useCustomFont_(false),
      normalColor_(normalColor),
      hoveredColor_(hoveredColor),
      pressedColor_(pressedColor),
      textColor_(textColor),
      currentState_(ButtonState::NORMAL)
{
}

Button::Button(Rectangle bounds, const std::string &text, const Font &font, float fontSize, float spacing,
               Color normalColor, Color hoveredColor, Color pressedColor, Color textColor,
               bool isVisible)
    : Widget(bounds, isVisible),
      text_(text),
      fontSize_(fontSize),
      spacing_(spacing),
      font_(font),
      useCustomFont_(true),
      normalColor_(normalColor),
      hoveredColor_(hoveredColor),
      pressedColor_(pressedColor),
      textColor_(textColor),
      currentState_(ButtonState::NORMAL) {
}

void Button::Update([[maybe_unused]] float deltaTime)
{
    Vector2 mousePosition = Core::Input::GetMousePosition();
    bool isMouseOver = IsPointInside(mousePosition);

    if (!isVisible_)
        return;
    if (!isMouseOver) {
        currentState_ = ButtonState::NORMAL;
        return;
    }
    if (Core::Input::IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        currentState_ = ButtonState::PRESSED;
    } else if (Core::Input::IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        currentState_ = ButtonState::HOVERED;
            onClickCallback_();
    } else {
        currentState_ = ButtonState::HOVERED;
    }
}

void Button::Draw()
{
    Color currentBgColor;
    float textX;
    float textY;
    Vector2 textSize;

    if (!isVisible_)
        return;
    if (currentState_ == ButtonState::HOVERED)
        currentBgColor = hoveredColor_;
    else if (currentState_ == ButtonState::PRESSED)
        currentBgColor = pressedColor_;
    else
        currentBgColor = normalColor_;

    Graphics::Shapes::DrawRectangle((int)bounds_.x, (int)bounds_.y, (int)bounds_.width, (int)bounds_.height, currentBgColor);
    textSize = useCustomFont_ ? ::MeasureTextEx(font_, text_.c_str(), (float)fontSize_, spacing_)
                                      : (Vector2){ (float)::MeasureText(text_.c_str(), fontSize_), (float)fontSize_ };
    textX = bounds_.x + (bounds_.width - textSize.x) / 2.0f;
    textY = bounds_.y + (bounds_.height - textSize.y) / 2.0f;
    if (useCustomFont_) {
        Graphics::Shapes::DrawTextEx(font_, text_.c_str(), {textX, textY}, (float)fontSize_, spacing_, textColor_);
    } else {
        Graphics::Shapes::DrawText(text_.c_str(), (int)textX, (int)textY, fontSize_, textColor_);
    }
}

void Button::SetOnClick(std::function<void()> callback)
{
    onClickCallback_ = callback;
}

void Button::SetText(const std::string &newText)
{
    text_ = newText;
}

void Button::SetFontSize(int newFontSize)
{
    fontSize_ = newFontSize;
}

void Button::SetColors(Color normalColor, Color hoveredColor, Color pressedColor)
{
    normalColor_ = normalColor;
    hoveredColor_ = hoveredColor;
    pressedColor_ = pressedColor;
}

void Button::SetTextColor(Color newTextColor)
{
    textColor_ = newTextColor;
}

void Button::SetFont(const Font &newFont)
{
    font_ = newFont;
    useCustomFont_ = true;
}

void Button::SetSpacing(float newSpacing)
{
    spacing_ = newSpacing;
}
} // namespace UI
} // namespace Raylib
