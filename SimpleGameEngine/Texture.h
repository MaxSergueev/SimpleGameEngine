#pragma once
#include <SDL_render.h>
#include <string>

#include "Renderer.h"

class Texture
{
private:
    std::string mFileName;
    SDL_Texture* mSdlTexture;
    int mWidth, mHeight;
public:
    Texture();
    ~Texture() = default;

    void Unload();
    bool Load(Renderer& pRenderer, const std::string& pFileName);
    inline SDL_Texture* GetSdlTexture() const {return mSdlTexture;}
    int GetWidth() const {return mWidth;}
    int GetHeight() const {return mHeight;}

    void UpdateInfo(int& pWidthOut, int& pHeightOut);
};
