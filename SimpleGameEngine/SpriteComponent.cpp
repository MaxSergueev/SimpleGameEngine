#include "SpriteComponent.h"

#include "Actor.h"
#include "Scene.h"

SpriteComponent::SpriteComponent(Actor* pOwner, Texture& pTexture, int pDrawOrder):
Component(pOwner),
mTexture(pTexture),
mDrawOrder(pDrawOrder),
mTexWidth(pTexture.GetWidth()),
mTexHeight(pTexture.GetHeight())
{
    mOwner->GetScene().GetRenderer().AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->GetScene().GetRenderer().RemoveSprite(this);
}

void SpriteComponent::SetTexture(const Texture& pTexture)
{
    mTexture = pTexture;
    mTexture.UpdateInfo(mTexWidth, mTexHeight);
}

void SpriteComponent::Draw(Renderer& pRenderer)
{
    Vector2 origin {mTexWidth/2.0f, mTexHeight/2.0f};
    pRenderer.DrawSprite(*mOwner, mTexture, Rectangle(), origin, Renderer::Flip::None); 
}
