/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Client
*/

#include "Client/Client.hpp"

namespace GUI {
Client::Client(std::shared_ptr<Network::NetworkManager> networkManager, 
               std::shared_ptr<GraphicalManager> graphicalManager)
    : m_networkManager(networkManager)
    , m_graphicalManager(graphicalManager)
{
}

Client::~Client()
{
}

void Client::runClient()
{
    if (m_networkManager) {
        m_networkManager->run();
        m_graphicalManager->runRender();
    } else {
        throw ClientException("NetworkManager is not initialized");
    }
}
}
