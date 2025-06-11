/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** GraphicTile
*/

#pragma once

#include "Raylib/Graphics/Model.hpp"
#include "Entity/MapTile/MapTile.hpp"

namespace GUI {

    /**
     * @brief Default scaling factor for the tile's 3D model.
     */
    constexpr float TILE_SCALE = 0.001f;

    /**
     * @brief Default spacing between island of the map
     */
    constexpr float TILE_SPACING = 5.5f;

/**
 * @class GraphicalTile
 * @brief Represents the visual, renderable version of a map tile.
 * @details This class extends the logical MapTile by adding graphical
 *          components necessary for rendering, such as a 3D model and
 *          a position in the 3D world. It bridges the gap between the
 *          game's state (MapTile) and its visual representation.
 * @see MapTile
 * @see AEntity
 * @see IEntity
 */
class GraphicalTile : public MapTile {
    public:
        /**
         * @brief Constructs a GraphicalTile object.
         * @param id Unique identifier for the tile.
         * @param position Logical position on the game map (x, y).
         * @param modelName File path to the 3D model for the tile.
         * @param graphicPosition Position in the 3D rendering world (x, y, z).
         * @param orientation Initial orientation of the tile (defaults to NORTH).
         */
        GraphicalTile(uint32_t id, Types::Position position,
            const std::string &modelName, Vector3 graphicPosition,
            Types::Orientation orientation = Types::Orientation::NORTH);
        
        /**
         * @brief Destructor for the GraphicalTile class.
         */
        ~GraphicalTile();

        /**
         * @brief Draw the map tile.
        */
        void draw() const override;

        Raylib::Graphics::Model m_model;    ///< The 3D model used for rendering the tile.
    protected:
        Vector3 m_graphicPosition;          ///< The position in 3D world coordinates for rendering.
        float m_scale;                      ///< The scale factor applied to the model when drawing.
};
}
