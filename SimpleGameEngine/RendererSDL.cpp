#include "RendererSDL.h"
#include "Log.h"
#include "Maths.h"

#include "SDL_image.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"

using namespace std;

RendererSDL::RendererSDL() :mSdlRenderer(nullptr)
{
}

bool RendererSDL::Initialize(Window& rWindow)
{
    mSdlRenderer = SDL_CreateRenderer(rWindow.GetSdlWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mSdlRenderer)
    {
        Log::Error(LogType::Video, "Failed to create SDL Renderer");
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        Log::Error(LogType::Video, "Unable to initialize SDL_Image");
        return false;
    }
    return true;
}

void RendererSDL::BeginDraw()
{
    SDL_SetRenderDrawColor(mSdlRenderer, 120, 120, 255, 255);
    SDL_RenderClear(mSdlRenderer);
}

void RendererSDL::Draw()
{
    DrawSprites();
}

void RendererSDL::DrawSprites()
{
    for (SpriteComponent* sprite : mSprites)
    {
        sprite->Draw(*this);
    }
}

void RendererSDL::DrawSprite(Actor& pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, Flip pFlip) const
{
    SDL_Rect destinationRect;
    Transform2D transform = pActor.GetTransform();
    destinationRect.w = static_cast<int>(pTex.GetWidth() * transform.GetScale().x);
    destinationRect.h = static_cast<int>(pTex.GetHeight() * transform.GetScale().y);
    destinationRect.x = static_cast<int>(transform.GetPosition().x - pOrigin.x);
    destinationRect.y = static_cast<int>(transform.GetPosition().y - pOrigin.y);

    SDL_Rect* sourceSDL = nullptr;
    if (pSourceRect != Rectangle::NullRect)
    {
        sourceSDL = new SDL_Rect{
            Maths::Round(pSourceRect.position.x),
            Maths::Round(pSourceRect.position.y),
            Maths::Round(pSourceRect.dimensions.x),
            Maths::Round(pSourceRect.dimensions.y) };
    }

    SDL_RenderCopyEx(mSdlRenderer,
        pTex.GetSdlTexture(),
        sourceSDL,
        &destinationRect,
        -Maths::ToDeg(transform.GetRotation().z),
        nullptr,
        static_cast<SDL_RendererFlip>(pFlip));

    delete sourceSDL;
}

void RendererSDL::AddSprite(SpriteComponent* pSprite)
{
    int spriteDrawOrder = pSprite->GetDrawOrder();
    vector<SpriteComponent*>::iterator sc;
    for (sc = mSprites.begin(); sc != mSprites.end(); ++sc)
    {
        if (spriteDrawOrder < (*sc)->GetDrawOrder()) break;
    }
    mSprites.insert(sc, pSprite);
}

void RendererSDL::RemoveSprite(SpriteComponent* pSprite)
{
    vector<SpriteComponent*>::iterator sc;
    sc = std::find(mSprites.begin(), mSprites.end(), pSprite);
    mSprites.erase(sc);
}

void RendererSDL::SetSpriteShaderProgram(ShaderProgram* shaderProgram)
{
}

void RendererSDL::EndDraw()
{
    SDL_RenderPresent(mSdlRenderer);
}

void RendererSDL::Close()
{
    SDL_DestroyRenderer(mSdlRenderer);
}

IRenderer::RendererType RendererSDL::GetType()
{
    return RendererType::SDL;
}

void RendererSDL::DrawRect(Rectangle& rRect)
{
    SDL_SetRenderDrawColor(mSdlRenderer, 255, 255, 255, 255);
    SDL_Rect sdlRect = rRect.ToSdlRect();
    SDL_RenderFillRect(mSdlRenderer, &sdlRect);
}

void RendererSDL::AddMesh(MeshComponent* pMesh)
{
}

void RendererSDL::RemoveMesh(MeshComponent* pMesh)
{
}

void RendererSDL::DrawMeshes()
{
}

void RendererSDL::SetViewMatrix(Matrix4Row view)
{
}
