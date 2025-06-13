/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Client
*/

#pragma once

#include <memory>
#include "NetworkManager/NetworkManager.hpp"
#include "Graphical/GraphicalManager.hpp"

namespace GUI {
class Client {
    public:
        Client(std::shared_ptr<Network::NetworkManager> networkManager, std::shared_ptr<GraphicalManager> graphicalManager);
        ~Client();

        void runClient();
    
        class ClientException : public std::exception {
            public:
                explicit ClientException(const std::string &message) : m_message(message) {}
                virtual const char* what() const noexcept override {
                    return m_message.c_str();
                }
            private:
                std::string m_message;
        };
    private:
        std::shared_ptr<Network::NetworkManager> m_networkManager;
        std::shared_ptr<GraphicalManager> m_graphicalManager;
};
}
