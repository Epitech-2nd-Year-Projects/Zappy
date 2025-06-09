/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Main
*/


#include <iostream>
#include "Macro.hpp"
#include "ArgumentsHandler/Arguments.hpp"
#include "NetworkManager/NetworkManager.hpp"
#include "Client/Client.hpp"

int main(int argc, [[maybe_unused]] char const *argv[])
{
    try {
        GUI::ArgumentsHandling::Arguments args(argc, argv);
        
        std::shared_ptr<GUI::GameState> gameState = std::make_shared<GUI::GameState>();
        GUI::Client client(std::make_shared<GUI::Network::NetworkManager>(gameState, args.getIp(), args.getPort(), args.isDebugMode()));

        client.runClient();
    } catch (const GUI::ArgumentsHandling::Arguments::ArgumentsException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return GUIMacro::EXIT_FAILLURE;
    } catch (const GUI::Client::ClientException &e) {
        std::cerr << "Client error: " << e.what() << std::endl;
        return GUIMacro::EXIT_FAILLURE;
    } catch (const GUI::Network::NetworkManager::NetworkException &e) {
        std::cerr << "Network error: " << e.what() << std::endl;
        return GUIMacro::EXIT_FAILLURE;
    }
    return GUIMacro::GUI_EXIT_SUCCESS;
}
