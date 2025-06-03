/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Texture
*/

#pragma once

#include <string>
#include <stdexcept>
#include <raylib.h>

namespace Raylib {
namespace Graphics {

class Texture {
public:
/**
     * @brief Constructs a Texture by loading an image from a specified file path.
     * @param filePath The path to the image file (e.g., .png, .jpg, .bmp).
     * @throws std::runtime_error if the texture fails to load.
     */
    explicit Texture(const std::string& filePath);

    /**
     * @brief Destructor. Unloads the Raylib Texture2D resource if it was loaded by this instance.
     */
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    /**
     * @brief Gets a const reference to the underlying Raylib Texture2D structure.
     * @return A const reference to Texture2D.
     */
    const Texture2D &GetRLTexture() const;

    /**
     * @brief Gets a mutable reference to the underlying Raylib Texture2D structure.
     * Use with caution.
     * @return A mutable reference to Texture2D.
     */
    Texture2D &GetRLTexture();

    /**
     * @brief Checks if the texture has been successfully loaded and is ready for use.
     * @return true if the texture's ID is valid, false otherwise.
     */
    bool IsReady() const;

    /**
     * @brief Gets the width of the texture.
     * @return The texture width in pixels.
     */
    int GetWidth() const;

    /**
     * @brief Gets the height of the texture.
     * @return The texture height in pixels.
     */
    int GetHeight() const;
private:
    Texture2D texture_;

    class TextureException : public std::exception {
    public:
        /**
         * @brief Constructs a TextureException with a specified error message.
         * @param message A string describing the error.
         */
        TextureException(const std::string &message) : message_(message) {}

        /**
         * @brief Returns a C-style character string describing the error.
         * @return A pointer to a null-terminated string.
         */
        const char *what() const noexcept override {
            return message_.c_str();
        };
    private:
        std::string message_;
    };
};

}
}
