#include "Texture.h"
#include <SDL_image.h>
#include "Log.h"

Texture::Texture() : mSdlTexture(nullptr), mWidth(0), mHeight(0)
{
}

bool Texture::Load(IRenderer& pRenderer, const std::string& pFileName)
{
    mFileName = pFileName;
    SDL_Surface* surface = IMG_Load(mFileName.c_str());
    if (!surface)
    {
        Log::Error(LogType::Application, "Failed to load texture file :" + mFileName);
        return false;
    }
    mWidth = surface->w;
    mHeight = surface->h;

    if (pRenderer.GetType() == IRenderer::RendererType::SDL)
        return LoadSdl(dynamic_cast<RendererSDL*>(&pRenderer), pFileName, surface);
    return LoadGl(dynamic_cast<RendererGl*>(&pRenderer), pFileName, surface);
}

void Texture::UpdateInfo(int& pWidthOut, int& pHeightOut)
{
    pWidthOut = mWidth;
    pHeightOut = mHeight;
}

bool Texture::LoadGl(RendererGl* pRenderer, const std::string& pFileName, SDL_Surface* pSurface)
{
    int format = 0;
    if (pSurface->format->format == SDL_PIXELFORMAT_RGB24)
    {
        format = GL_RGB;
    }
    else if (pSurface->format->format == SDL_PIXELFORMAT_RGBA32)
    {
        format = GL_RGBA;
    }
    glGenTextures(1, &mTextureId);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, pSurface->pixels);
    SDL_FreeSurface(pSurface);
    Log::Info("Loaded GL texture : " + mFileName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

bool Texture::LoadSdl(RendererSDL* pRenderer, const std::string& pFileName, SDL_Surface* pSurface)
{
    mSdlTexture = SDL_CreateTextureFromSurface(pRenderer->ToSdlRenderer(), pSurface);
    SDL_FreeSurface(pSurface);
    if (!mSdlTexture)
    {
        Log::Error(LogType::Render, "Failed to convert surface to texture :" + mFileName);
        return false;
    }
    Log::Info("Loaded SDL texture : " + mFileName);
    return true;
}

void Texture::Unload()
{
    if (mSdlTexture) SDL_DestroyTexture(mSdlTexture);
    else glDeleteTextures(1, &mTextureId);
}

void Texture::SetActive() const
{
    glBindTexture(GL_TEXTURE_2D, mTextureId);
}
