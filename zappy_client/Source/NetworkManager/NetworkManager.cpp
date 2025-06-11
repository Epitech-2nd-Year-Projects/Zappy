/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** NetworkManager
*/

#include <iostream>
#include <stdlib.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sstream>
#include "NetworkManager/NetworkManager.hpp"
#include "GameState/Types/GameTypes.hpp"
#include "EventManager/EventType.hpp"

namespace GUI {
namespace Network {
NetworkManager::NetworkManager(std::shared_ptr<GameState> gameState, const std::string &ip, const int port, bool debugMode)
    : m_ip(ip), m_port(port), m_debugMode(debugMode), m_connected(false), m_gameState(std::move(gameState))
{
    m_functions["msz"] = [this](std::vector<std::string> &msg) {msz(msg);};
    m_functions["bct"] = [this](std::vector<std::string> &msg) {bct(msg);};
    m_functions["tna"] = [this](std::vector<std::string> &msg) {tna(msg);};

    m_functions["pnw"] = [this](std::vector<std::string> &msg) {pnw(msg);};
    m_functions["ppo"] = [this](std::vector<std::string> &msg) {ppo(msg);};
    m_functions["plv"] = [this](std::vector<std::string> &msg) {plv(msg);};
    m_functions["pin"] = [this](std::vector<std::string> &msg) {pin(msg);};
    m_functions["pex"] = [this](std::vector<std::string> &msg) {pex(msg);};
    m_functions["pbc"] = [this](std::vector<std::string> &msg) {pbc(msg);};
    m_functions["pic"] = [this](std::vector<std::string> &msg) {pic(msg);};
    m_functions["pie"] = [this](std::vector<std::string> &msg) {pie(msg);};
    m_functions["pfk"] = [this](std::vector<std::string> &msg) {pfk(msg);};
    m_functions["pdr"] = [this](std::vector<std::string> &msg) {pdr(msg);};
    m_functions["pgt"] = [this](std::vector<std::string> &msg) {pgt(msg);};
    m_functions["pdi"] = [this](std::vector<std::string> &msg) {pdi(msg);};

    m_functions["enw"] = [this](std::vector<std::string> &msg) {enw(msg);};
    m_functions["ebo"] = [this](std::vector<std::string> &msg) {ebo(msg);};
    m_functions["edi"] = [this](std::vector<std::string> &msg) {edi(msg);};

    m_functions["sgt"] = [this](std::vector<std::string> &msg) {sgt(msg);};
    m_functions["sst"] = [this](std::vector<std::string> &msg) {sst(msg);};
    m_functions["seg"] = [this](std::vector<std::string> &msg) {seg(msg);};
    m_functions["smg"] = [this](std::vector<std::string> &msg) {smg(msg);};
    m_functions["suc"] = [this](std::vector<std::string> &msg) {suc(msg);};
    m_functions["sbp"] = [this](std::vector<std::string> &msg) {sbp(msg);};
}

NetworkManager::~NetworkManager()
{
    if (m_connected) {
        disconnect();
    }
    if (m_receiveThread.joinable()) {
        m_receiveThread.join();
    }
    if (m_debugMode) {
        std::cout << "NetworkManager destroyed" << std::endl;
    }
}

// Functions to handle commands

uint32_t NetworkManager::strToInt(const std::string &str) const
{
    try {
        return std::stoul(str);
    } catch (const std::invalid_argument &e) {
        throw NetworkException("Invalid argument: " + str);
    } catch (const std::out_of_range &e) {
        throw NetworkException("Out of range: " + str);
    }
}

void NetworkManager::msz(std::vector<std::string> &command)
{
    EventManager::MapSizeEvent event;

    if (command.size() < 3)
        return;
    event.width = strToInt(command[1]);
    event.height = strToInt(command[2]);
    m_gameState->mapSizeCommand(event);
    if (m_debugMode) {
        std::cout << "Map size: " << event.width << "x" << event.height << std::endl;
    }
}

void NetworkManager::bct(std::vector<std::string> &command)
{
    EventManager::TileContentEvent event;
    Types::Position position;

    if (command.size() < 10)
        return;
    position.x = strToInt(command[1]);
    position.y = strToInt(command[2]);
    event.position = position;
    for (size_t i = 3; i < command.size(); ++i) {
        event.resources[i - 3] = strToInt(command[i]);
    }
    m_gameState->tileContentCommand(event);
    if (m_debugMode) {
        std::cout << "Tile at (" << position.x << ", " << position.y << ") has resources: ";
        for (const auto &res : event.resources) {
            std::cout << res << " ";
        }
        std::cout << std::endl;
    }
}

void NetworkManager::tna(std::vector<std::string> &command)
{
    EventManager::TeamNamesEvent event;

    if (command.size() != 2) {
        return;
    }
    event.teamNames = command[1];
    m_gameState->teamNameCommand(event);
    if (m_debugMode) {
        std::cout << "Team names: " << event.teamNames << std::endl;
    }
}

void NetworkManager::pnw(std::vector<std::string> &command)
{
    EventManager::PlayerConnectionEvent event;
    Types::PlayerId playerId;
    Types::Position position;
    Types::Orientation orientation;
    Types::PlayerLvl level;
    std::string teamName;

    if (command.size() != 7) {
        return;
    }
    playerId = strToInt(command[1]);
    position.x = strToInt(command[2]);
    position.y = strToInt(command[3]);
    orientation = static_cast<Types::Orientation>(strToInt(command[4]));
    level = strToInt(command[5]);
    teamName = command[6];
    event.playerId = playerId;
    event.position = position;
    event.orientation = orientation;
    event.level = level;
    event.teamName = teamName;
    m_gameState->playerConnectionCommand(event);
    if (m_debugMode) {
        std::cout << "Player " << playerId << " connected at (" << position.x << ", " << position.y
                  << ") facing " << static_cast<int>(orientation) << ", level: " << level
                  << ", team: " << teamName << std::endl;
    }
}

void NetworkManager::ppo(std::vector<std::string> &command)
{
    Types::PlayerId playerId;
    Types::Position position;
    Types::Orientation orientation;
    EventManager::PlayerMovedEvent event;

    if (command.size() < 5)
        return;
    playerId = strToInt(command[1]);
    position.x = strToInt(command[2]);
    position.y = strToInt(command[3]);
    orientation = static_cast<Types::Orientation>(strToInt(command[4]));
    event.playerId = playerId;
    event.newPosition = position;
    event.newOrientation = orientation;
    m_gameState->playerMovedCommand(event);
    if (m_debugMode) {
        std::cout << "Player " << playerId << " moved to (" << position.x << ", " << position.y
                  << ") facing " << static_cast<int>(orientation) << std::endl;
    }
}

void NetworkManager::plv(std::vector<std::string> &command)
{
    EventManager::PlayerLevelEvent event;
    Types::PlayerId playerId;
    Types::PlayerLvl level;

    if (command.size() != 3) {
        return;
    }
    playerId = strToInt(command[1]);
    level = strToInt(command[2]);
    event.playerId = playerId;
    event.newLevel = level;
    m_gameState->playerLevelCommand(event);
    if (m_debugMode) {
        std::cout << "Player " << playerId << " leveled up to " << level << std::endl;
    }
}

void NetworkManager::pin(std::vector<std::string> &command)
{
    EventManager::PlayerInventoryEvent event;
    Types::PlayerId playerId;
    Types::ResourceArray inventory;

    if (command.size() != 11) {
        return;
    }
    playerId = strToInt(command[1]);
    event.playerId = playerId;
    event.position.x = strToInt(command[2]);
    event.position.y = strToInt(command[3]);
    for (size_t i = 0; i < 8; ++i) {
        inventory[i] = strToInt(command[i + 4]);
    }
    event.inventory = inventory;
    m_gameState->playerInventoryCommand(event);
    if (m_debugMode) {
        std::cout << "Player " << playerId << " inventory at (" << event.position.x << ", "
                  << event.position.y << "): ";
        for (const auto &res : inventory) {
            std::cout << res << " ";
        }
        std::cout << std::endl;
    }
}

void NetworkManager::pex(std::vector<std::string> &command)
{
    EventManager::PlayerExpulsionEvent event;

    if (command.size() != 2) {
        return;
    }
    event.playerId = strToInt(command[1]);
    m_gameState->playerExpulsionCommand(event);
    if (m_debugMode) {
        std::cout << "Player " << event.playerId << " has been expelled" << std::endl;
    }
}

void NetworkManager::pbc(std::vector<std::string> &command)
{
    EventManager::PlayerBroadcastEvent event;

    if (command.size() != 3) {
        return;
    }
    event.senderId = strToInt(command[1]);
    event.message = command[2];
    m_gameState->playerBroadcastCommand(event);
    if (m_debugMode) {
        std::cout << "Player " << event.senderId << " broadcasted: " << event.message << std::endl;
    }
}

void NetworkManager::pic(std::vector<std::string> &command)
{
    EventManager::IncantationStartEvent event;
    Types::Position position;
    Types::PlayerLvl level;

    if (command.size() < 5) {
        return;
    }
    position.x = strToInt(command[1]);
    position.y = strToInt(command[2]);
    level = strToInt(command[3]);
    for (size_t i = 4; i < command.size(); ++i) {
        event.participants.push_back(strToInt(command[i]));
    }
    event.position = position;
    m_gameState->incantationStartCommand(event);
    if (m_debugMode) {
        std::cout << "Incantation started at (" << position.x << ", " << position.y
                  << ") for level " << level << " with participants: ";
        for (const auto &participant : event.participants) {
            std::cout << participant << " ";
        }
        std::cout << std::endl;
    }
}

void NetworkManager::pie(std::vector<std::string> &command)
{
    EventManager::IncantationEndEvent event;

    if (command.size() != 4) {
        return;
    }
    event.position.x = strToInt(command[1]);
    event.position.y = strToInt(command[2]);
    event.result = strToInt(command[3]) != 0;
    m_gameState->incantationEndCommand(event);
    if (m_debugMode) {
        std::cout << "Incantation ended at (" << event.position.x << ", " << event.position.y
                  << ") with result: " << (event.result ? "success" : "failure") << std::endl;
    }
}

void NetworkManager::pfk(std::vector<std::string> &command)
{
    EventManager::PlayerForkEvent event;

    if (command.size() != 2) {
        return;
    }
    event.playerId = strToInt(command[1]);
    m_gameState->playerForkCommand(event);
    if (m_debugMode) {
        std::cout << "Player " << event.playerId << " has forked" << std::endl;
    }
}

void NetworkManager::pdr([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::pgt([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::pdi([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::enw([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::ebo([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::edi([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::sgt([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::sst([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::seg([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::smg([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::suc([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::sbp([[maybe_unused]]std::vector<std::string> &command)
{
}

// !Functions to handle commands

void NetworkManager::connectToServer()
{
    struct addrinfo hints = {};
    struct addrinfo *res = nullptr;
    std::string portStr = std::to_string(m_port);
    int err = 0;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    err = getaddrinfo(m_ip.c_str(), portStr.c_str(), &hints, &res);
    if (err != 0)
        throw NetworkException(std::string("getaddrinfo failed: ") + gai_strerror(err));
    m_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (m_socket < 0) {
        freeaddrinfo(res);
        throw NetworkException("Failed to create socket");
    }
    if (connect(m_socket, res->ai_addr, res->ai_addrlen) < 0) {
        freeaddrinfo(res);
        throw NetworkException("Connection failed");
    }
    freeaddrinfo(res);
    m_connected = true;
    if (m_debugMode)
        std::cout << "Connected to server at " << m_ip << ":" << m_port << std::endl;

}

void NetworkManager::disconnect()
{
    if (m_connected) {
        close(m_socket);
        m_connected = false;
        if (m_debugMode)
            std::cout << "Disconnected from server" << std::endl;
    }
}

std::string NetworkManager::getMessages() const
{
    if (m_messageQueue.empty())
        return "";
    return m_messageQueue.front();
}

std::size_t NetworkManager::getBytesAvailable() const
{
    int bytesAvailable;

    if (ioctl(m_socket, FIONREAD, &bytesAvailable) < 0)
        throw NetworkException("Error getting bytes available");
    return static_cast<std::size_t>(bytesAvailable);
}

void NetworkManager::clearMessages()
{
    m_messages.clear();
}

std::string NetworkManager::createMessage()
{
    std::string message;
    auto it = m_messages.begin();

    while (it != m_messages.end()) {
        std::size_t pos = it->find('\n');
        if (pos != std::string::npos) {
            message += it->substr(0, pos + 1);
            if (pos + 1 < it->size())
                *it = it->substr(pos + 1);
            else
                it = m_messages.erase(it);
            break;
        } else {
            message += *it;
            it = m_messages.erase(it);
        }
    }
    return message;
}

bool NetworkManager::isEndOfMessage(const std::string &message)
{
    if (message.find('\n') != std::string::npos) {
        m_messageQueue.push(createMessage());
        return true;
    }
    return false;
}

std::vector<std::string> NetworkManager::splitByWord(const std::string &input)
{
    std::vector<std::string> words;
    size_t start = 0;
    size_t end = 0;
    
    while ((start = input.find_first_not_of(" \n", end)) != std::string::npos) {
        end = input.find_first_of(" \n", start);
        if (end == std::string::npos) {
            words.push_back(input.substr(start));
            break;
        } else {
            words.push_back(input.substr(start, end - start));
        }
    }
    return words;
}

void NetworkManager::runCommands()
{
    std::vector<std::string> commands;

    while (!m_messageQueue.empty()) {
        std::string message = m_messageQueue.front();
        m_messageQueue.pop();
        commands = splitByWord(message);
        for (const auto &function : m_functions) {
            if (commands[0] != function.first)
                continue;    
            function.second(commands);
            break;
        }
    }
}

void NetworkManager::readMessages()
{
    std::size_t bytesAvailable = 0;
    char *buffer = nullptr;
    ssize_t bytesRead;

    while (m_connected) {
        bytesAvailable = getBytesAvailable();
        if (bytesAvailable == 0)
            continue;
        buffer = static_cast<char *>(calloc(bytesAvailable + 1, sizeof(char)));
        bytesRead = recv(m_socket, buffer, bytesAvailable, 0);
        if (bytesRead < 0)
            throw NetworkException("Error reading from socket");
        else if (bytesRead == 0) {
            disconnect();
            return;
        }
        std::string message(buffer);
        m_messages.push_back(message);
        isEndOfMessage(message);
        if (!m_messageQueue.empty())
            runCommands();
        if (m_debugMode)
            std::cout << "Received message: " << message << std::endl;
    }
}

void NetworkManager::sendMessage(const std::string &message)
{
    if (!m_connected)
        throw NetworkException("Not connected to server");
    if (send(m_socket, message.c_str(), message.size(), 0) < 0)
        throw NetworkException("Error sending message");
    if (m_debugMode)
        std::cout << "Sent message: " << message << std::endl;
}

void NetworkManager::run()
{
    m_receiveThread = std::thread([this]()
    {
        if (!m_connected)
            connectToServer();
        readMessages();
    });
}
}
}
