/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** GraphicalPLayer
*/

#pragma once

#include "Raylib/Graphics/Model.hpp"
#include "Raylib/Graphics/Animation.hpp"
#include "Entity/Player/Player.hpp"

namespace GUI {

constexpr float PLAYER_SCALE = 0.35f;
constexpr float PlAYER_Y_OFFSET = 0.0f;
constexpr float TILE_OFFSET = 5.0f;

/**
 * @class GraphicalPlayer
 * @brief Represents the visual representation of a player in the game world.
 *
 * This class extends the logical Player class by adding graphical components
 * necessary for rendering, such as a 3D model and animation. It is responsible
 * for drawing the player on the screen.
 * @see Player
 * @see AEntity
 */
class GraphicalPlayer : public Player {
    public:
        /**
         * @brief Constructs a new GraphicalPlayer object.
         * @param id The unique entity identifier.
         * @param pId The unique player identifier from the server.
         * @param position The player's logical position on the game grid.
         * @param level The player's current level.
         * @param teamName The name of the team the player belongs to.
         * @param modelName The asset path for the player's 3D model.
         * @param animationName The asset path for the player's animation.
         * @param graphicPosition The player's coordinates in 3D world space for rendering.
         * @param orientation The direction the player is facing.
         */
        GraphicalPlayer(uint32_t id, Types::PlayerId pId,
            Types::Position position, uint32_t level,
            const std::string &teamName, const std::string &modelName,
            const std::string &animationName, Vector3 graphicPosition,
            Types::Orientation orientation = Types::Orientation::NORTH);

        /**
         * @brief Destroys the GraphicalPlayer object.
         */
        ~GraphicalPlayer();

        /**
         * @brief Renders the player's 3D model in the game world.
         * @note This method overrides the pure virtual `draw()` from the IEntity interface.
         */
        void draw() const;

        Raylib::Graphics::Model m_model; ///< The 3D model for the player.
        Raylib::Graphics::Animation
            m_animation; ///< The animation data for the player's model.

    protected:
        Vector3 m_graphicPosition; ///< The player's position in 3D space for rendering.
        float m_scale; ///< The scaling factor applied to the model when drawing.
};
}
