/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Animation
*/

#pragma once

#include "Raylib/Graphics/Model.hpp"
#include <string>
#include <map>
#include <stdexcept>

namespace Raylib {
namespace Graphics {

/**
 * @brief Simple animation controller for a 3D model, using raw pointers for Raylib's animation array.
 * Provides functionality to load, play, update, and control model animations
 * (looping, one-shot) in a C++-friendly manner with RAII principles.
 * Note: Uses raw pointer for Raylib ModelAnimation array, managing ownership manually.
 */
class Animation {
public:
    /**
     * @brief Constructs an Animation controller by loading animations from a model file.
     * @param modelFilePath_ The path to the model file containing animations (e.g., .glb, .iqm).
     * @throws AnimationException if animations fail to load.
     */
    explicit Animation(const std::string &modelFilePath_);

    /**
     * @brief Destructor. Unloads all loaded Raylib ModelAnimation resources.
     */
    ~Animation();

    Animation(const Animation&) = delete;
    Animation &operator=(const Animation &) = delete;

    /**
     * @brief Starts playing an animation by its index.
     * Automatically resets frame counter if animation changes.
     * @param animIndex_ The index of the animation to play.
     * @param loop_ True if the animation should loop, false for one-shot playback.
     */
    void Play(int animIndex_, bool loop_);

    /**
     * @brief Stops the currently playing animation.
     */
    void Stop();

    /**
     * @brief Updates the current animation's frame and applies it to the provided model.
     * This method must be called once per frame.
     * @param model_ A mutable reference to the Raylib::Graphics::Model to animate.
     * @return true if an animation is currently active and updating, false if stopped or invalid.
     */
    bool Update(Model& model_);

    /**
     * @brief Checks if the animation controller currently has any animations loaded.
     * @return true if animations are loaded, false otherwise.
     */
    bool HasAnimations() const;

    /**
     * @brief Gets the total number of animations loaded.
     * @return The count of loaded animations.
     */
    int GetAnimationCount() const;

    /**
     * @brief Gets the name of a specific animation by index.
     * @param index_ The index of the animation.
     * @return The name of the animation, or an empty string if index is invalid.
     */
    std::string GetAnimationName(int index_) const;

    /**
     * @brief Gets the current animation index being played.
     * @return The index of the current animation, or -1 if stopped.
     */
    int GetCurrentAnimIndex() const { return currentAnimIndex_; }

    /**
     * @brief Gets the current frame of the playing animation.
     * @return The current frame counter.
     */
    int GetCurrentFrame() const { return animFrameCounter_; }

    /**
     * @brief Checks if the currently playing animation is a one-shot and has finished.
     * For one-shot animations, this becomes true when the last frame is reached.
     * @return true if a one-shot animation has completed, false otherwise.
     */
    bool IsOneShotFinished() const;
private:
    ::ModelAnimation *anims_; ///< Raw pointer to the array of Raylib ModelAnimation structures. Owned by this class.
    int animCount_; ///< Number of animations in the array.
    int currentAnimIndex_;    ///< Index of the currently playing animation.
    int animFrameCounter_;    ///< Current frame in the animation.
    bool shouldLoop_;          ///< True if current animation should loop.
    bool isOneShotActive_;     ///< True if a one-shot animation is currently running.

    /**
     * @brief Internal helper to load animations from a file.
     * @param modelFilePath_ The path to the model file.
     * @throws AnimationException if loading fails.
     */
    void loadAnimations_(const std::string &modelFilePath_);

    /**
     * @brief Internal helper to check if an animation index is valid.
     * @param index_ The index to check.
     * @return true if the index is within bounds, false otherwise.
     */
    bool isValidAnimIndex_(int index_) const;

    /**
     * @brief Internal helper to clean up Raylib animation resources.
     * Sets anims_ to nullptr and animCount_ to 0 after unloading.
     */
    void unloadInternalAnims_();

    class AnimationException : public std::exception {
    public:
        /**
         * @brief Constructs a WindowException with a specified error message.
         * @param message A string describing the error.
         */
        AnimationException(const std::string &message) : message_(message) {}

        /**
         * @brief Returns a C-style character string describing the error.
         * @return A pointer to a null-terminated string.
         */
        const char *what() const noexcept override
        {
            return message_.c_str();
        };
    private:
        std::string message_;
    };
};
}
}
