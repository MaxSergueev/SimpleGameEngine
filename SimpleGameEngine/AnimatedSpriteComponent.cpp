#include "AnimatedSpriteComponent.h"

#include "Time.h"

AnimatedSpriteComponent::AnimatedSpriteComponent(Actor* pOwner, const vector<Texture*>& pTexture, int pDrawOrder) :
    SpriteComponent(pOwner, *pTexture[0], pDrawOrder), mCurrentFrame(0.0f), mAnimFps(24.0f)
{
    SetAnimationTextures(pTexture);
}

AnimatedSpriteComponent::~AnimatedSpriteComponent()
{
}

void AnimatedSpriteComponent::SetAnimationTextures(const vector<Texture*>& pTextures)
{
    mAnimationTextures = pTextures;
    if (mAnimationTextures.size() > 0) {
        SetTexture(*mAnimationTextures[0]);
    }
}

void AnimatedSpriteComponent::SetAnimationFps(float pFps)
{
    mAnimFps = pFps;
}

void AnimatedSpriteComponent::Update()
{
    SpriteComponent::Update();
    if (mAnimationTextures.size() == 0) return;
    mCurrentFrame += mAnimFps * Time::deltaTime;
    while (mCurrentFrame >= mAnimationTextures.size())
    {
        mCurrentFrame -= mAnimationTextures.size();
    }
    SetTexture(*mAnimationTextures[static_cast<int>(mCurrentFrame)]);
}

