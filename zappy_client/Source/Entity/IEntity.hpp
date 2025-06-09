/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Entities
*/

#pragma once

#include "GameState/Types/GameTypes.hpp"

namespace GUI {
class IEntity {
    public:
        virtual ~IEntity() = default;

        virtual void update() = 0;
        virtual void setPosition(Types::Position position) = 0;
        virtual void setOrientation(Types::Orientation orientation) = 0;
};
}
