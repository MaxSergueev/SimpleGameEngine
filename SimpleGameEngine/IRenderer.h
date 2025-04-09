#pragma once
#include "Actor.h"
#include "Rectangle.h"
#include "Window.h"
#include "ShaderProgram.h"

class Texture;
class SpriteComponent;
class MeshComponent;

class IRenderer
{
public:
    enum class Flip
    {
        None = SDL_FLIP_NONE,
        Horizontal = SDL_FLIP_HORIZONTAL,
        Vertical = SDL_FLIP_VERTICAL
    };

    enum class RendererType
    {
        SDL,
        OPENGL
    };
    virtual ~IRenderer() = default;

    virtual bool Initialize(Window& rWindow) = 0;
    virtual void BeginDraw() = 0;
    virtual void Draw() = 0;
    virtual void DrawSprites() = 0;
    virtual void EndDraw() = 0;
    virtual void Close() = 0;
    virtual RendererType GetType() = 0;

    virtual void DrawSprite(Actor& pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, Flip pFlip = Flip::None) const = 0;
    virtual void AddSprite(SpriteComponent* pSprite) = 0;
    virtual void RemoveSprite(SpriteComponent* pSprite) = 0;

    virtual void SetSpriteShaderProgram(ShaderProgram* shaderProgram) = 0;

    virtual void AddMesh(MeshComponent* pMesh) = 0;
    virtual void RemoveMesh(MeshComponent* pMesh) = 0;
    virtual void DrawMeshes() = 0;

    virtual void SetViewMatrix(Matrix4Row view) = 0;


};
