/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** NetworkManager
*/

#ifndef NETWORKMANAGER_HPP_
    #define NETWORKMANAGER_HPP_

#include <string>
#include <thread>
#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace GUI {
namespace Network {
class NetworkManager {
    public:
        /**
         * @brief Construct a new NetworkManager object
         * @param ip The IP address of the server
         * @param port The port to connect to
         * @param debugMode Enable debug mode if true
         */
        NetworkManager(const std::string &ip, const int port, bool debugMode = false);

        /**
         * @brief Destroy the NetworkManager object
         */
        ~NetworkManager();

        /**
         * @brief Main loop to run the network manager
         */
        void run();

        /**
         * @brief Send a message to the server
         * @param message The message to send
         * @throws NetworkException if the connection fails or message sending fails
         * @note The message should be formatted according to the server's protocol
         */
        void sendMessage(const std::string &message);
        
        /**
         * @brief Connect to the server
         */
        void connectToServer();
        
        /**
         * @brief Disconnect from the server
         */
        void disconnect();
        
        /**
         * @brief Get all messages as a single string
         * @return std::string Concatenated messages
         */
        std::string getMessages() const;
        
        /**
         * @brief Exception class for network errors
         */
        class NetworkException : public std::exception {
            public:
                /**
                 * @brief Construct a new NetworkException object
                 * @param message The exception message
                 */
                explicit NetworkException(const std::string &message) : m_message(message) {}
    
                /**
                 * @brief Get the exception message
                 * @return const char* Exception message
                 */
                virtual const char* what() const noexcept override {
                    return m_message.c_str();
                }
            private:
                std::string m_message; ///< Exception message
        };

    private:
        /**
         * @brief Read messages from the server
         */
        void readMessages();

        /**
         * @brief Clear all stored messages
         */
        void clearMessages();

        /**
         * @brief Run all received commands
         */
        void runCommands();

        /**
         * @brief Get the number of bytes available to read
         * @return std::size_t Number of bytes available
         */
        std::size_t getBytesAvailable() const;

        /**
         * @brief Check if the message is complete (end of message)
         * @param message The message to check
         * @return true If the message is complete
         * @return false Otherwise
         */
        bool isEndOfMessage(const std::string &message);

        /**
         * @brief Push a message to the message queue
         * @param message The message to push
         */
        void pushMessage(const std::string &message);

        /**
         * @brief Create a message for the queue
         * @return std::string The created message (command and parameters)
         */
        std::string createMessage();

        /**
         * @brief Split a string by newline characters
         * @param input The input string
         * @return std::vector<std::string> Vector of split strings
         */
        std::vector<std::string> splitByNewline(const std::string &input);

        /**
         * @brief Handle the "msz" command (map size)
         * @param command The command and its parameters
         */
        void msz(std::vector<std::string> &command);

        /**
         * @brief Handle the "bct" command (block content)
         * @param command The command and its parameters
         */
        void bct(std::vector<std::string> &command);

        /**
         * @brief Handle the "tna" command (team names)
         * @param command The command and its parameters
         */
        void tna(std::vector<std::string> &command);

        /**
         * @brief Handle the "pnw" command (new player)
         * @param command The command and its parameters
         */
        void pnw(std::vector<std::string> &command);

        /**
         * @brief Handle the "ppo" command (player position)
         * @param command The command and its parameters
         */
        void ppo(std::vector<std::string> &command);

        /**
         * @brief Handle the "plv" command (player level)
         * @param command The command and its parameters
         */
        void plv(std::vector<std::string> &command);

        /**
         * @brief Handle the "pin" command (player inventory)
         * @param command The command and its parameters
         */
        void pin(std::vector<std::string> &command);

        /**
         * @brief Handle the "pex" command (player expulsion)
         * @param command The command and its parameters
         */
        void pex(std::vector<std::string> &command);

        /**
         * @brief Handle the "pbc" command (player broadcast)
         * @param command The command and its parameters
         */
        void pbc(std::vector<std::string> &command);

        /**
         * @brief Handle the "pic" command (incantation start)
         * @param command The command and its parameters
         */
        void pic(std::vector<std::string> &command);

        /**
         * @brief Handle the "pie" command (incantation end)
         * @param command The command and its parameters
         */
        void pie(std::vector<std::string> &command);

        /**
         * @brief Handle the "pfk" command (player lays egg)
         * @param command The command and its parameters
         */
        void pfk(std::vector<std::string> &command);

        /**
         * @brief Handle the "pdr" command (player drops resource)
         * @param command The command and its parameters
         */
        void pdr(std::vector<std::string> &command);

        /**
         * @brief Handle the "pgt" command (player gets resource)
         * @param command The command and its parameters
         */
        void pgt(std::vector<std::string> &command);

        /**
         * @brief Handle the "pdi" command (player dies)
         * @param command The command and its parameters
         */
        void pdi(std::vector<std::string> &command);

        /**
         * @brief Handle the "enw" command (egg laid by player)
         * @param command The command and its parameters
         */
        void enw(std::vector<std::string> &command);

        /**
         * @brief Handle the "ebo" command (egg hatches)
         * @param command The command and its parameters
         */
        void ebo(std::vector<std::string> &command);

        /**
         * @brief Handle the "edi" command (egg dies)
         * @param command The command and its parameters
         */
        void edi(std::vector<std::string> &command);

        /**
         * @brief Handle the "sgt" command (get time unit)
         * @param command The command and its parameters
         */
        void sgt(std::vector<std::string> &command);

        /**
         * @brief Handle the "sst" command (set time unit)
         * @param command The command and its parameters
         */
        void sst(std::vector<std::string> &command);

        /**
         * @brief Handle the "seg" command (end of game)
         * @param command The command and its parameters
         */
        void seg(std::vector<std::string> &command);

        /**
         * @brief Handle the "smg" command (server message)
         * @param command The command and its parameters
         */
        void smg(std::vector<std::string> &command);

        /**
         * @brief Handle the "suc" command (unknown command)
         * @param command The command and its parameters
         */
        void suc(std::vector<std::string> &command);

        /**
         * @brief Handle the "sbp" command (bad parameters)
         * @param command The command and its parameters
         */
        void sbp(std::vector<std::string> &command);

        const std::string m_ip; ///< Server IP address
        const int m_port; ///< Server port
        struct sockaddr_in m_serverAddress; ///< Server address structure
        std::map<std::string, std::function<void(std::vector<std::string> &)>> m_functions; ///< Command handlers
        std::queue<std::string> m_messageQueue; ///< Queue of incoming messages
        std::vector<std::string> m_messages; ///< Stored messages
        std::thread m_receiveThread; ///< Thread for receiving messages
        int m_socket; ///< Socket descriptor
        bool m_debugMode; ///< Debug mode flag
        bool m_connected; ///< Connection status
    
};
}
}

#endif /* !NETWORKMANAGER_HPP_ */
