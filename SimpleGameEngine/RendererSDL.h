#pragma once
#include "Actor.h"
#include "Rectangle.h"
#include "Window.h"
#include "IRenderer.h"

class Texture;

/**
 * @brief SDL-based renderer implementation for 2D graphics
 *
 * RendererSDL provides SDL rendering functionality primarily focused on 2D sprite
 * rendering. It implements the IRenderer interface but provides stub implementations
 * for 3D mesh functionality since SDL is primarily a 2D rendering API. Manages
 * SDL renderer context and sprite draw order for proper layering.
 */
class RendererSDL : public IRenderer
{
private:
    SDL_Renderer* mSdlRenderer;             ///< SDL renderer context for drawing operations
    std::vector<SpriteComponent*> mSprites; ///< Collection of sprites to render in draw order

public:
    /**
     * @brief Default constructor - initializes with null renderer
     */
    RendererSDL();

    RendererSDL(const RendererSDL&) = delete;

    /**
     * @brief Initializes SDL renderer with the specified window
     * @param rWindow The window to create the SDL renderer for
     * @return True if initialization was successful
     */
    bool Initialize(Window& rWindow) override;

    /**
     * @brief Begins a new rendering frame by clearing the screen
     */
    void BeginDraw() override;

    /**
     * @brief Renders all registered sprites
     */
    void Draw() override;

    /**
     * @brief Renders all registered sprite components
     */
    void DrawSprites() override;

    /**
     * @brief Finalizes the current frame and presents it
     */
    void EndDraw() override;

    /**
     * @brief Shuts down the renderer and releases SDL resources
     */
    void Close() override;

    /**
     * @brief Gets the renderer type identifier
     * @return RendererType::SDL
     */
    virtual RendererType GetType() override;

    /**
     * @brief Gets the underlying SDL renderer for direct access
     * @return Pointer to the SDL_Renderer object
     */
    SDL_Renderer* ToSdlRenderer() const { return mSdlRenderer; }

    /**
     * @brief Draws a filled rectangle (utility function)
     * @param rRect The rectangle to draw
     */
    void DrawRect(Rectangle& rRect);

    /**
     * @brief Renders a single sprite with specified parameters
     * @param pActor The actor containing transform information
     * @param pTex The texture to render
     * @param pSourceRect Source rectangle within the texture
     * @param pOrigin Origin point for rotation and scaling
     * @param pFlip Flip operation to apply (default: None)
     */
    void DrawSprite(Actor& pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, Flip pFlip = Flip::None) const;

    /**
     * @brief Registers a sprite component for rendering
     * @param pSprite The sprite component to add to the render queue
     */
    void AddSprite(SpriteComponent* pSprite);

    /**
     * @brief Unregisters a sprite component from rendering
     * @param pSprite The sprite component to remove from the render queue
     */
    void RemoveSprite(SpriteComponent* pSprite);

    /**
     * @brief Sets the shader program for sprites (not applicable for SDL)
     * @param shaderProgram Unused parameter - SDL doesn't use custom shaders
     */
    void SetSpriteShaderProgram(ShaderProgram* shaderProgram) override;

    /**
     * @brief Stub implementation - SDL doesn't support 3D mesh rendering
     * @param pMesh Unused parameter
     */
    void AddMesh(MeshComponent* pMesh) override;

    /**
     * @brief Stub implementation - SDL doesn't support 3D mesh rendering
     * @param pMesh Unused parameter
     */
    void RemoveMesh(MeshComponent* pMesh) override;

    /**
     * @brief Stub implementation - SDL doesn't support 3D mesh rendering
     */
    void DrawMeshes() override;

    /**
     * @brief Stub implementation - SDL doesn't use view matrices
     * @param view Unused parameter
     */
    void SetViewMatrix(Matrix4Row view) override;
};
