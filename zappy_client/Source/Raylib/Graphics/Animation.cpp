/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** Animation
*/

#include "Raylib/Graphics/Animation.hpp"

namespace Raylib {
namespace Graphics {

Animation::Animation(const std::string &modelFilePath_)
    : anims_(nullptr),
      animCount_(0),
      currentAnimIndex_(-1),
      animFrameCounter_(0),
      shouldLoop_(false),
      isOneShotActive_(false)
{    
    loadAnimations_(modelFilePath_);
    if (animCount_ > 0) {
        currentAnimIndex_ = 0;
        shouldLoop_ = true;
    }
}

Animation::~Animation()
{
    unloadInternalAnims_();
}

void Animation::Play(int animIndex_, bool loop_)
{
    if (!isValidAnimIndex_(animIndex_)){
        Stop();
        return;
    }
    if (currentAnimIndex_ != animIndex_){
        currentAnimIndex_ = animIndex_;
        animFrameCounter_ = 0;
    }    
    shouldLoop_ = loop_;
    isOneShotActive_ = !loop_;
}

void Animation::Stop()
{
    currentAnimIndex_ = -1;
    animFrameCounter_ = 0;
    shouldLoop_ = false;
    isOneShotActive_ = false;
}

bool Animation::Update(Model &model_)
{
    if (!HasAnimations() || currentAnimIndex_ == -1 || !isValidAnimIndex_(currentAnimIndex_)) {
        return false;
    }
    ::ModelAnimation &currentAnim_data_ = anims_[currentAnimIndex_];

    if (isOneShotActive_ && animFrameCounter_ >= currentAnim_data_.frameCount - 1) {
        Stop();
        return false;
    }
    animFrameCounter_++;
    if (animFrameCounter_ >= currentAnim_data_.frameCount) {
        if (shouldLoop_) {
            animFrameCounter_ = 0;
        } else {
            animFrameCounter_ = currentAnim_data_.frameCount - 1;
        }
    }
    ::UpdateModelAnimation(model_.GetRLModel(), currentAnim_data_, animFrameCounter_);
    return true;
}

bool Animation::HasAnimations() const
{
    return anims_ != nullptr && animCount_ > 0;
}

int Animation::GetAnimationCount() const
{
    return animCount_;
}

std::string Animation::GetAnimationName(int index_) const
{
    if (isValidAnimIndex_(index_) && anims_[index_].name[0] != '\0') {
        return anims_[index_].name;
    }
    return "";
}

bool Animation::IsOneShotFinished() const
{
    if (isOneShotActive_ && isValidAnimIndex_(currentAnimIndex_)) {
        return animFrameCounter_ >= anims_[currentAnimIndex_].frameCount - 1;
    }
    return false;
}

void Animation::loadAnimations_(const std::string& modelFilePath_)
{
    int count_ = 0;

    anims_ = ::LoadModelAnimations(modelFilePath_.c_str(), &count_);
    if (anims_ != nullptr && count_ > 0) {
        animCount_ = count_;
    } else {
        anims_ = nullptr;
        animCount_ = 0;
        throw AnimationException("Failed to load animations from model: " + modelFilePath_);
    }
}

bool Animation::isValidAnimIndex_(int index_) const
{
    return index_ >= 0 && index_ < animCount_;
}

void Animation::unloadInternalAnims_()
{
    if (anims_ != nullptr) {
        ::UnloadModelAnimations(anims_, animCount_);
        anims_ = nullptr;
        animCount_ = 0;
    }
}
}
}
