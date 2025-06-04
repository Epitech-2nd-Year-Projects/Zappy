/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Client
*/

#include "Client/Client.hpp"

namespace GUI {
Client::Client(std::shared_ptr<Network::NetworkManager> networkManager)
    : m_networkManager(std::move(networkManager))
{
}

Client::~Client()
{
}

void Client::runClient()
{
    if (m_networkManager) {
        m_networkManager->run();
    } else {
        throw ClientException("NetworkManager is not initialized");
    }
}
}
