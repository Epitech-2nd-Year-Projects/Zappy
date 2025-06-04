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

/**
 * @class Arguments
 * @brief Handles and validates command line arguments for the Zappy GUI client
 *
 * This class parses command line arguments for the Zappy GUI application.
 * It processes the IP/hostname (-h), port number (-p), and debug mode (-d) options.
 * Validation is performed on each argument to ensure proper format.
 */
class Arguments {
    public:
        /**
         * @brief Constructs an Arguments object by parsing command line arguments
         * @param ac Argument count (argc from main)
         * @param av Argument values (argv from main)
         * @throw ArgumentsException if arguments are invalid or missing
         */
        Arguments(int ac, const char **av);

        /**
         * @brief Destroys the Arguments object
         */
        ~Arguments();

        /**
         * @brief Gets the parsed IP address or hostname
         * @return The IP address or hostname as a string
         */
        const std::string &getIp() const;

        /**
         * @brief Gets the parsed port number
         * @return The port number as an integer
         */
        int getPort() const;

        /**
         * @brief Checks if debug mode is enabled
         * @return True if debug mode is enabled, false otherwise
         */
        bool isDebugMode() const;

        /**
         * @class ArgumentsException
         * @brief Exception thrown when command line arguments are invalid
         *
         * This exception is thrown when the provided command line arguments
         * don't meet the required format or constraints.
         */
        class ArgumentsException : public std::exception {
            public:
            /**
             * @brief Constructs an ArgumentsException with a specific error message
             * @param message The error message describing what went wrong
             */
            explicit ArgumentsException(const std::string &message) : m_message(message) {}
            
            /**
             * @brief Gets the exception message
             * @return C-style string containing the error message
             */
            virtual const char* what() const noexcept override {
                return m_message.c_str();
            }
            
            private:
            std::string m_message;  /**< The error message */
        };
        
    private:
        /**
         * @brief Sets and validates the IP address or hostname
         * @param ip The IP address or hostname string to validate and store
         * @throw ArgumentsException if the IP format is invalid
         */
        void setIp(const char *ip);
        
        /**
         * @brief Sets and validates the port number
         * @param port The port number string to validate and store
         * @throw ArgumentsException if the port is invalid
         */
        void setPort(const char *port);

        /**
         * @brief Validates the format of an IP address or hostname
         * @param ip The IP address or hostname to validate
         * @throw ArgumentsException if the format is invalid
         */
        void checkFormatIp(const char *ip);
        
        std::string m_ip;     /**< The validated IP address or hostname */
        int m_port;           /**< The validated port number */
        bool m_debugMode;     /**< Flag indicating if debug mode is enabled */
};

}
}

#endif /* !ARGUMENTS_HPP_ */
