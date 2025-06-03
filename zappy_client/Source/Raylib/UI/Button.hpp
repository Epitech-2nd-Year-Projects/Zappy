/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Button
*/

#pragma once

#include "Raylib/UI/Widget.hpp"
#include "Raylib/Core/Input.hpp"
#include "Raylib/Graphics/Shapes.hpp"
#include <string>
#include <functional>

namespace Raylib {
namespace UI {

class Button : public Widget {
public:
    /**
     * @brief Enum for button states.
     */
    enum class ButtonState {
        NORMAL,
        HOVERED,
        PRESSED
    };

/**
     * @brief Constructs a Button widget with text.
     * @param bounds Rectangle defining the button's position and size.
     * @param text The text to display on the button.
     * @param fontSize The font size for the text.
     * @param normalColor The background color when in normal state.
     * @param hoveredColor The background color when hovered.
     * @param pressedColor The background color when pressed.
     * @param textColor The color of the button's text.
     * @param isVisible Initial visibility state.
     */
    Button(Rectangle bounds_, const std::string &text, int fontSize,
           Color normalColor, Color hoveredColor, Color pressedColor, Color textColor,
           bool isVisible = true);

    /**
     * @brief Constructs a Button widget with text and a custom font.
     * @param bounds Rectangle defining the button's position and size.
     * @param text The text to display on the button.
     * @param font The custom Raylib Font structure to use.
     * @param fontSize The font size for the text.
     * @param spacing The character spacing.
     * @param normalColor The background color when in normal state.
     * @param hoveredColor The background color when hovered.
     * @param pressedColor The background color when pressed.
     * @param textColor The color of the button's text.
     * @param isVisible Initial visibility state.
     */
    Button(Rectangle bounds, const std::string &text, const Font &font, float fontSize, float spacing,
           Color normalColor, Color hoveredColor, Color pressedColor, Color textColor,
           bool isVisible = true);

    /**
     * @brief Updates the button's state based on mouse input.
     * @param deltaTime The time elapsed since the last frame.
     */
    void Update(float deltaTime) override;

    /**
     * @brief Draws the button on the screen, applying appropriate colors based on its state.
     */
    void Draw() override;

    /**
     * @brief Sets the callback function to be executed when the button is clicked.
     * @param callback The function to set.
     */
    void SetOnClick(std::function<void()> callback);

    /**
     * @brief Sets the text displayed on the button.
     * @param newText The new text string.
     */
    void SetText(const std::string &newText);

    /**
     * @brief Sets the font size for the button's text.
     * @param newFontSize The new font size.
     */
    void SetFontSize(int newFontSize);

    /**
     * @brief Sets the colors for the button's states.
     * @param normalColor The new normal background color.
     * @param hoveredColor The new hovered background color.
     * @param pressedColor The new pressed background color.
     */
    void SetColors(Color normalColor, Color hoveredColor, Color pressedColor);

    /**
     * @brief Sets the color of the button's text.
     * @param newTextColor The new text color.
     */
    void SetTextColor(Color newTextColor);

    /**
     * @brief Sets a custom font for the button's text.
     * @param newFont The custom Raylib Font structure.
     */
    void SetFont(const Font &newFont);

    /**
     * @brief Sets the character spacing for the button's text.
     * @param newSpacing The new spacing value.
     */
    void SetSpacing(float newSpacing);

private:
    std::string text_;
    int fontSize_;
    float spacing_;
    Font  font_;
    bool  useCustomFont_;
    Color normalColor_;
    Color hoveredColor_;
    Color pressedColor_;
    Color textColor_;

    ButtonState currentState_;
    std::function<void()> onClickCallback_;
};
}
}
