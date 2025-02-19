#pragma once
#include "Actor.h"
#include "Rectangle.h"
#include "Window.h"

class SpriteComponent;
class Texture;

class Renderer
{
private:
    SDL_Renderer* mSdlRenderer;
    std::vector<SpriteComponent*> mSprites;
public:
    enum class Flip
    {
        None = SDL_FLIP_NONE,
        Horizontal = SDL_FLIP_HORIZONTAL,
        Vertical = SDL_FLIP_VERTICAL
    };
    Renderer();
    Renderer(const Renderer&) = delete;
    //Renderer& operator= (const Renderer&) = delete;

    bool Initialize(Window& rWindow);
    void BeginDraw();
    void Draw();
    void DrawSprites();
    void EndDraw();
    void Close();

    SDL_Renderer* ToSdlRenderer() const {return mSdlRenderer;}

    void DrawRect(Rectangle& rRect);
    void DrawSprite(Actor& pActor,const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, Flip pFlip = Flip::None) const;
    void AddSprite(SpriteComponent* pSprite);
    void RemoveSprite(SpriteComponent* pSprite);
};
