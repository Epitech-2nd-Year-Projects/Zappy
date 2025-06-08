/*
** EPITECH PROJECT, 2025
** Zappy [WSL: Ubuntu]
** File description:
** Arguments
*/

#include <iostream>
#include <regex>
#include "Arguments.hpp"
#include "Macro.hpp"

namespace GUI {
namespace ArgumentsHandling {
Arguments::Arguments(int ac, const char **av)
{
    if (ac == 2 && (std::string(av[1]) == "-h" || std::string(av[1]) == "-help")) {
        std::cout << "Usage: " << av[0] << " -p <port> -h <ip/hostname>" << std::endl;
        exit(0);
    } 
    if (ac < GUIMacro::MIN_ARG_NUMBER || ac > GUIMacro::MAX_ARG_NUMBER) {
        throw ArgumentsException("Usage: " + std::string(av[0]) + " -p <port> -h <ip/hostname>");
    }
    for (int i = 1; i < ac; i += 2) {
        std::string arg(av[i]);
        if (arg == "-p") {
            setPort(av[i + 1]);
        } else if (arg == "-h") {
            setIp(av[i + 1]);
        } else if (arg == "-d") {
            m_debugMode = true;
            --i;
        }
    }
}

Arguments::~Arguments()
{
}

void Arguments::setIp(const char *ip)
{
    checkFormatIp(ip);
    m_ip = ip;
}

void Arguments::setPort(const char *port)
{
    char *endptr;
    long int portNumber = std::strtol(port, &endptr, 10);

    if (*endptr != '\0' || portNumber < 0 || portNumber > 65535)
        throw ArgumentsException("Invalid port number: " + std::string(port));
    m_port = static_cast<int>(portNumber);
}

void Arguments::checkFormatIp(const char *ip)
{
    std::regex ipv4_regex(
        R"(^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$)"
    );
    std::regex hostname_regex(
        R"(^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\-]*[a-zA-Z0-9])\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\-]*[A-Za-z0-9])$)"
    );
    std::string ip_str(ip);

    if (std::regex_match(ip_str, ipv4_regex))
        return;
    if (std::regex_match(ip_str, hostname_regex))
        return;
    throw ArgumentsException("Invalid IP address or hostname: " + ip_str);
}

const std::string &Arguments::getIp() const
{
    return m_ip;
}

int Arguments::getPort() const
{
    return m_port;
}

bool Arguments::isDebugMode() const
{
    return m_debugMode;
}

}
}
