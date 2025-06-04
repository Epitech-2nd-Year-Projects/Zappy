/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Arguments
*/

#ifndef ARGUMENTS_HPP_
    #define ARGUMENTS_HPP_

    #include <exception>
    #include <string>

namespace GUI {
namespace ArgumentsHandling {
class Arguments {
    public:
        Arguments(int ac, const char **av);
        ~Arguments();

        const std::string &getIp() const;
        int getPort() const;
        bool isDebugMode() const;

        class ArgumentsException : public std::exception {
            public:
            explicit ArgumentsException(const std::string &message) : m_message(message) {}
            virtual const char* what() const noexcept override {
                return m_message.c_str();
            }
            private:
            std::string m_message;
        };
    private:
        void setIp(const char *ip);
        void setPort(const char *port);

        void checkFormatIp(const char *ip);
        std::string m_ip;
        int m_port;
        bool m_debugMode;

};
}
}

#endif /* !ARGUMENTS_HPP_ */
