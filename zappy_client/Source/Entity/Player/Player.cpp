/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Player
*/

#include "Entity/Player/Player.hpp"

namespace GUI {
Player::Player(uint32_t id, Types::PlayerId pId, Types::Position position,
                uint32_t level, const std::string &teamName, Types::Orientation orientation)
    : AEntity(id, position, orientation)
    , m_teamName(teamName)
    , m_level(level)
    , m_playerId(pId)
{
    m_inventory.fill(0);
}

Player::~Player()
{
}

Types::ResourceArray Player::getInventory() const { return m_inventory; }

std::string Player::getTeamName() const { return m_teamName; }

uint32_t Player::getLevel() const { return m_level; }

uint32_t Player::getLife() const { return m_life; }

Types::PlayerId Player::getPlayerId() const { return m_playerId; }

bool Player::isAlive() const { return Alive; }

void Player::setInventory(const Types::ResourceArray &inventory)
{
    m_inventory = inventory;
}

void Player::setTeamName(std::string &teamId)
{
    m_teamName = teamId;
}

void Player::setLevel(uint32_t level)
{
    m_level = level;
}

void Player::setLife(uint32_t life)
{
    m_life = life;
}

void Player::setAlive(bool alive)
{
    Alive = alive;
}

void Player::lvlUp()
{
    m_level++;
}

void Player::removeResource(Types::ResourceType resourceType, std::size_t amount)
{
    if (resourceType >= Types::ResourceType::COUNT)
        return;
    auto &resourceCount = m_inventory[static_cast<size_t>(resourceType)];
    if (resourceCount >= amount) {
        resourceCount -= amount;
    } else {
        resourceCount = 0;
    }
}

void Player::addResource(Types::ResourceType resourceType, std::size_t amount)
{
    if (resourceType < Types::ResourceType::COUNT) {
        m_inventory[static_cast<size_t>(resourceType)] += amount;
    }
}
}
