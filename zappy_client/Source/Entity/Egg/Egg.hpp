/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Egg
*/

#pragma once

#include "Entity/AEntity.hpp"
#include "GameState/Types/GameTypes.hpp"

namespace GUI {
class Egg : public AEntity {
    public:
        Egg(uint32_t id, Types::Position position, std::string &teamName,
            Types::Orientation orientation = Types::Orientation::NORTH);
        ~Egg() = default;

        void setHatched(bool hatched);
        bool isHatched() const;
    protected:
        std::string m_teamName;
        bool m_hatched;
};
}
