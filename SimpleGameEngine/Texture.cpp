#include "Texture.h"
#include <SDL_image.h>
#include "Log.h"

Texture::Texture(): mSdlTexture(nullptr), mWidth(0), mHeight(0)
{
}

void Texture::Unload()
{
    if(mSdlTexture) SDL_DestroyTexture(mSdlTexture);
}

bool Texture::Load(Renderer& pRenderer, const std::string& pFileName)
{
    mFileName = pFileName;
    SDL_Surface* surface = IMG_Load(mFileName.c_str());
    if(!surface)
    {
        Log::Error(LogType::Application, "Failed to load texture file :"+mFileName);
        return false;
    }
    mWidth = surface->w;
    mHeight = surface->h;

    //Create texture from surface
    mSdlTexture = SDL_CreateTextureFromSurface(pRenderer.ToSdlRenderer(), surface);
    SDL_FreeSurface(surface);
    if(!mSdlTexture)
    {
        Log::Error(LogType::Render, "Failed to convert surface to texture :"+mFileName);
        return false;
    }
    Log::Info("Loaded texture : "+mFileName);
    return true;
}

void Texture::UpdateInfo(int& pWidthOut, int& pHeightOut)
{
    pWidthOut = mWidth;
    pHeightOut = mHeight;
}
