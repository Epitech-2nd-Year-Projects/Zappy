/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Main
*/

#include "Macro.hpp"

int main(int argc, [[maybe_unused]] char const *argv[])
{
    if (argc != GUIMacro::ARG_NUMBER)
        return GUIMacro::EXIT_FAILLURE;
    return GUIMacro::EXIT_SUCCESS;
}
