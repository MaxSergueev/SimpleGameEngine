#pragma once
#include <SDL_render.h>
#include <string>

#include "RendererSDL.h"
#include "RendererGL.h"

class Texture
{
private:
	std::string mFileName;
	SDL_Texture* mSdlTexture;
	int mWidth, mHeight;
	unsigned int mTextureId;
	bool LoadSdl(RendererSDL* pRenderer, const std::string& pFileName, SDL_Surface* pSurface);
	bool LoadGl(RendererGl* pRenderer, const std::string& pFileName, SDL_Surface* pSurface);

public:
	Texture();
	~Texture() = default;

	void Unload();
	bool Load(IRenderer& pRenderer, const std::string& pFileName);
	void SetActive() const;
	inline SDL_Texture* GetSdlTexture() const { return mSdlTexture; }
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }

	void UpdateInfo(int& pWidthOut, int& pHeightOut);
};

