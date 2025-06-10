/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** GraphicalTypes
*/

#pragma once

#include <cstdio>
#include <string>
#include <utility>

struct WindowInformation {
    std::string windowName;
    std::size_t windowWidth;
    std::size_t windowHeight;

    WindowInformation &operator=(const std::pair<std::size_t,
        std::size_t> &dimensions) {
        windowWidth = dimensions.first;
        windowHeight = dimensions.second;
        return *this;
    }
};

struct MapSize
{
    std::size_t width;
    std::size_t height;
};

