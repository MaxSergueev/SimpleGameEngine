#pragma once
#include "Component.h"
#include "Texture.h"

class SpriteComponent : public Component
{
protected:
    Texture mTexture;
    int mDrawOrder;
    int mTexWidth;
    int mTexHeight;
    bool mFlipX = false;
public:
    SpriteComponent(Actor* pOwner, Texture& pTexture, int pDrawOrder = 100);
    virtual ~SpriteComponent();
    SpriteComponent() = delete;
    SpriteComponent(const SpriteComponent&) = delete;
    SpriteComponent& operator= (const SpriteComponent&) = delete;

    virtual void SetTexture(const Texture& pTexture);
    void SetFlipX(bool FlipX) { mFlipX = FlipX; };
    virtual void Draw(IRenderer& pRenderer);

    //Getters
    int GetDrawOrder() const {return mDrawOrder;}
    int GetTexWidth() const {return mTexWidth;}
    int GetTexHeight() const {return mTexHeight;}
};
