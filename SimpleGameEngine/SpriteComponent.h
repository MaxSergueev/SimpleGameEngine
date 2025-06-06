#pragma once
#include "Component.h"
#include "Texture.h"

/**
 * @brief Component that renders 2D sprites for actors
 *
 * SpriteComponent provides 2D sprite rendering functionality by managing textures
 * and draw order. It automatically registers with the scene's renderer and handles
 * texture flipping for directional sprites. The component calculates proper origin
 * points for centered sprite rendering and integrates with both SDL and OpenGL renderers.
 */
class SpriteComponent : public Component
{
protected:
    Texture mTexture;   ///< The texture to render for this sprite
    int mDrawOrder;     ///< Rendering order (lower values drawn first)
    int mTexWidth;      ///< Cached texture width for performance
    int mTexHeight;     ///< Cached texture height for performance
    bool mFlipX = false; ///< Whether to flip the sprite horizontally

public:
    /**
     * @brief Constructs a sprite component with the specified texture
     * @param pOwner The actor that owns this sprite component
     * @param pTexture The texture to render for this sprite
     * @param pDrawOrder Rendering priority (default: 100, lower values drawn first)
     */
    SpriteComponent(Actor* pOwner, Texture& pTexture, int pDrawOrder = 100);

    /**
     * @brief Virtual destructor - unregisters from renderer
     */
    virtual ~SpriteComponent();

    SpriteComponent() = delete;
    SpriteComponent(const SpriteComponent&) = delete;
    SpriteComponent& operator= (const SpriteComponent&) = delete;

    /**
     * @brief Changes the texture used by this sprite
     * @param pTexture The new texture to use for rendering
     */
    virtual void SetTexture(const Texture& pTexture);

    /**
     * @brief Sets horizontal flipping for the sprite
     * @param FlipX True to flip horizontally, false for normal orientation
     */
    void SetFlipX(bool FlipX) { mFlipX = FlipX; };

    /**
     * @brief Renders the sprite using the specified renderer
     * @param pRenderer The renderer interface to use for drawing
     */
    virtual void Draw(IRenderer& pRenderer);

    /**
     * @brief Gets the rendering draw order
     * @return The draw order value (lower values rendered first)
     */
    int GetDrawOrder() const { return mDrawOrder; }

    /**
     * @brief Gets the cached texture width
     * @return Width of the texture in pixels
     */
    int GetTexWidth() const { return mTexWidth; }

    /**
     * @brief Gets the cached texture height
     * @return Height of the texture in pixels
     */
    int GetTexHeight() const { return mTexHeight; }
};

