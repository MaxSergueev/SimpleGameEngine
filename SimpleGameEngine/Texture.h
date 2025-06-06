#pragma once
#include <SDL_render.h>
#include <string>

#include "RendererSDL.h"
#include "RendererGL.h"

/**
 * @brief Cross-platform texture wrapper supporting both SDL and OpenGL rendering
 *
 * Texture encapsulates texture loading and management for both SDL and OpenGL
 * rendering backends. It automatically detects the renderer type and loads
 * textures in the appropriate format, providing a unified interface for
 * texture operations across different rendering systems.
 */
class Texture
{
private:
    std::string mFileName;      ///< Original filename of the loaded texture
    SDL_Texture* mSdlTexture;   ///< SDL texture object (for SDL renderer)
    int mWidth, mHeight;        ///< Dimensions of the texture in pixels
    unsigned int mTextureId;    ///< OpenGL texture ID (for OpenGL renderer)

    /**
     * @brief Loads texture for SDL rendering backend
     * @param pRenderer Pointer to the SDL renderer
     * @param pFileName Name of the texture file
     * @param pSurface SDL surface containing the loaded image data
     * @return True if loading was successful
     */
    bool LoadSdl(RendererSDL* pRenderer, const std::string& pFileName, SDL_Surface* pSurface);

    /**
     * @brief Loads texture for OpenGL rendering backend
     * @param pRenderer Pointer to the OpenGL renderer
     * @param pFileName Name of the texture file
     * @param pSurface SDL surface containing the loaded image data
     * @return True if loading was successful
     */
    bool LoadGl(RendererGl* pRenderer, const std::string& pFileName, SDL_Surface* pSurface);

public:
    /**
     * @brief Default constructor - creates uninitialized texture
     */
    Texture();

    /**
     * @brief Default destructor
     */
    ~Texture() = default;

    /**
     * @brief Releases texture resources for the current rendering backend
     */
    void Unload();

    /**
     * @brief Loads texture from file using the specified renderer
     * @param pRenderer Reference to the renderer interface
     * @param pFileName Path to the texture file to load
     * @return True if loading was successful
     */
    bool Load(IRenderer& pRenderer, const std::string& pFileName);

    /**
     * @brief Activates this texture for OpenGL rendering
     */
    void SetActive() const;

    /**
     * @brief Gets the SDL texture object for SDL rendering
     * @return Pointer to the SDL_Texture object
     */
    inline SDL_Texture* GetSdlTexture() const { return mSdlTexture; }

    /**
     * @brief Gets the texture width in pixels
     * @return Width of the texture
     */
    int GetWidth() const { return mWidth; }

    /**
     * @brief Gets the texture height in pixels
     * @return Height of the texture
     */
    int GetHeight() const { return mHeight; }

    /**
     * @brief Updates external variables with texture dimensions
     * @param pWidthOut Reference to store the texture width
     * @param pHeightOut Reference to store the texture height
     */
    void UpdateInfo(int& pWidthOut, int& pHeightOut);
};
