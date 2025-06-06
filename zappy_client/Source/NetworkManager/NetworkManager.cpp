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
#include "NetworkManager.hpp"

namespace GUI {
namespace Network {
NetworkManager::NetworkManager(const std::string &ip, const int port, bool debugMode)
    : m_ip(ip), m_port(port), m_debugMode(debugMode), m_connected(false)
{
    m_functions["mszx"] = [this](std::vector<std::string> &msg) {msz(msg);};
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

void NetworkManager::msz([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::bct([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::tna([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::pnw([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::ppo([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::plv([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::pin([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::pex([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::pbc([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::pic([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::pie([[maybe_unused]]std::vector<std::string> &command)
{
}

void NetworkManager::pfk([[maybe_unused]]std::vector<std::string> &command)
{
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

    std::cout << "Connecting to server at " << m_ip << " : " << m_port << "..." << std::endl;
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

std::vector<std::string> NetworkManager::splitByNewline(const std::string& input)
{
    std::vector<std::string> lines;
    std::istringstream stream(input);
    std::string line;

    while (std::getline(stream, line)) {
        lines.push_back(line);
    }
    return lines;
}

void NetworkManager::runCommands()
{
    std::vector<std::string> commands;

    while (!m_messageQueue.empty()) {
        std::string message = m_messageQueue.front();
        m_messageQueue.pop();
        commands = splitByNewline(message);
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
    if (!m_connected)
        connectToServer();
    m_receiveThread = std::thread([this]() { readMessages(); });
}
}
}
