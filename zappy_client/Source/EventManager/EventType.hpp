/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** EventType
*/

#pragma once

#include "EventManager/IEvent.hpp"
#include "GameState/Types/GameTypes.hpp"

namespace GUI {
namespace EventManager {

struct PlayerMovedEvent : public IEvent {
    Types::PlayerId playerId;
    Types::Position newPosition;
    Types::Orientation newOrientation;
};
}
}