/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Player
*/

#pragma once

#include "Entity/AEntity.hpp"

namespace GUI {
class Player : public AEntity {
    public:
        Player(uint32_t id, std::shared_ptr<Types::Position> position,
                uint32_t level, std::string &teamName, Types::Orientation orientation = Types::Orientation::NORTH);
        ~Player() = 0;

        Types::ResourceArray getInventory() const;
        std::string getTeamName() const;
        uint32_t getLevel() const;
        uint32_t getLife() const;
        bool isAlive() const;

        void setInventory(const Types::ResourceArray &inventory);
        void setTeamName(std::string &teamId);
        void setLevel(uint32_t level);
        void setLife(uint32_t life);
        void setAlive(bool alive);

        void removeResource(Types::ResourceType resourceType, std::size_t amount = 1);
        void addResource(Types::ResourceType resourceType, std::size_t amount = 1);
        void lvlUp();
    private:
        Types::ResourceArray m_inventory;
        std::string m_teamName;
        uint32_t m_level;
        uint32_t m_life = 126;
        bool Alive = true;
};
}
