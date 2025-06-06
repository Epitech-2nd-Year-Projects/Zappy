/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Client
*/

#pragma once

#include <memory>
#include "NetworkManager/NetworkManager.hpp"

namespace GUI {
class Client {
    public:
        Client(std::shared_ptr<Network::NetworkManager> networkManager);
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
};
}
