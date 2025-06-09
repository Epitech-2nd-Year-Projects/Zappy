/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** AEntity
*/

#pragma once

#include <memory>
#include "Entity/IEntity.hpp"
#include "GameState/Types/ProtocolTypes.hpp"
#include "Raylib/Graphics/Animation.hpp"

namespace GUI {
class AEntity : public IEntity {
    public:
        AEntity(uint32_t id, std::shared_ptr<Types::Position> position,
                Types::Orientation orientation = Types::Orientation::NORTH);
        ~AEntity() = default;

        void setPosition(Types::Position position) override;
        void setOrientation(Types::Orientation orientation) override;
    protected:
        uint32_t m_id;
        std::shared_ptr<Types::Position> m_position;
        Types::Orientation m_orientation;
};
}
