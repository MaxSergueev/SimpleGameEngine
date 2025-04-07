#pragma once
#include "Actor.h"
#include "Rectangle.h"
#include "Window.h"
#include "IRenderer.h"

class Texture;

class RendererSDL: public IRenderer
{
private:
    SDL_Renderer* mSdlRenderer;
    std::vector<SpriteComponent*> mSprites;
public:
    RendererSDL();
    RendererSDL(const RendererSDL&) = delete;
    //Renderer& operator= (const Renderer&) = delete;

    bool Initialize(Window& rWindow) override;
    void BeginDraw() override;
    void Draw() override;
    void DrawSprites() override;
    void EndDraw() override;
    void Close() override;
    virtual RendererType GetType() override;

    SDL_Renderer* ToSdlRenderer() const {return mSdlRenderer;}

    void DrawRect(Rectangle& rRect);

    void DrawSprite(Actor& pActor,const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, Flip pFlip = Flip::None) const;
    void AddSprite(SpriteComponent* pSprite);
    void RemoveSprite(SpriteComponent* pSprite);

	void SetShaderProgram(ShaderProgram* shaderProgram) override;

    void AddMesh(MeshComponent* pMesh) override;
    void RemoveMesh(MeshComponent* pMesh) override;
    void DrawMeshes() override;
};
