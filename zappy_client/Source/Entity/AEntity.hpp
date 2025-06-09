/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** AEntity
*/

#pragma once

#include <memory>
#include "Entity/IEntity.hpp"
#include "Raylib/Graphics/Animation.hpp"
#include "GameState/Types/GameTypes.hpp"

namespace GUI {
class AEntity : public IEntity {
    public:
        AEntity(uint32_t id, Types::Position position,
                Types::Orientation orientation = Types::Orientation::NORTH);
        ~AEntity() = default;

        void setPosition(Types::Position position) override;
        void setOrientation(Types::Orientation orientation) override;
    protected:
        uint32_t m_id;
        Types::Position m_position;
        Types::Orientation m_orientation;
};
}
