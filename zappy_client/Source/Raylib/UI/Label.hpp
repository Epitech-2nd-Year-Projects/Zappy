/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Label
*/

#pragma once

#include "Raylib/UI/Widget.hpp"
#include "Raylib/Graphics/Shapes.hpp"
#include <string>

namespace Raylib {
namespace UI {
    class Label : public Widget {
public:
    /**
     * @brief Constructs a Label widget.
     * @param bounds Rectangle defining the label's position and size.
     * @param text The initial text to display.
     * @param fontSize The font size for the text.
     * @param color The color of the text.
     * @param isVisible Initial visibility state.
     */
    Label(Rectangle bounds, const std::string &text, int fontSize, Color color, bool isVisible = true);

    /**
     * @brief Constructs a Label widget with a custom font.
     * @param bounds Rectangle defining the label's position and size.
     * @param text The initial text to display.
     * @param font The custom Raylib Font structure to use.
     * @param fontSize The font size for the text.
     * @param spacing The character spacing.
     * @param color The color of the text.
     * @param isVisible Initial visibility state.
     */
    Label(Rectangle bounds, const std::string &text, const Font &font, float fontSize, float spacing, Color color, bool isVisible_ = true);

    /**
     * @brief Updates the label's state (does nothing for a static label).
     * @param deltaTime The time elapsed since the last frame.
     */
    void Update(float deltaTime) override;

    /**
     * @brief Draws the label on the screen.
     */
    void Draw() override;

    /**
     * @brief Sets the text displayed by the label.
     * @param newText The new string to display.
     */
    void SetText(const std::string &newText);

    /**
     * @brief Sets the color of the label's text.
     * @param newColor The new color.
     */
    void SetColor(Color newColor);

    /**
     * @brief Sets the font size of the label's text.
     * @param newFontSize The new font size.
     */
    void SetFontSize(int newFontSize);

    /**
     * @brief Sets the font for the label (using Raylib's Font struct).
     * @param newFont The new Font structure.
     */
    void SetFont(const Font &newFont);

    /**
     * @brief Sets the character spacing for the label.
     * @param newSpacing The new spacing value.
     */
    void SetSpacing(float newSpacing);

private:
    std::string text_;
    int fontSize_;
    Color color_;
    Font  font_;
    float spacing_;
    bool  useCustomFont_;
};
}
}
