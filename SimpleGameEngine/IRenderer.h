#pragma once
#include "Actor.h"
#include "Rectangle.h"
#include "Window.h"
#include "ShaderProgram.h"

class Texture;
class SpriteComponent;
class MeshComponent;

/**
 * @brief Abstract interface for rendering systems in the engine
 *
 * IRenderer defines the contract for all rendering implementations, providing
 * methods for initialization, drawing operations, and resource management.
 * Supports both 2D sprite rendering and 3D mesh rendering with different
 * backend implementations (SDL, OpenGL).
 */
class IRenderer
{
public:
    /**
     * @brief Enumeration for sprite flip operations
     */
    enum class Flip
    {
        None = SDL_FLIP_NONE,           ///< No flipping
        Horizontal = SDL_FLIP_HORIZONTAL, ///< Flip horizontally
        Vertical = SDL_FLIP_VERTICAL    ///< Flip vertically
    };

    /**
     * @brief Enumeration for available renderer types
     */
    enum class RendererType
    {
        SDL,        ///< SDL-based 2D renderer
        OPENGL      ///< OpenGL-based 3D renderer
    };

    /**
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~IRenderer() = default;

    /**
     * @brief Initializes the renderer with the specified window
     * @param rWindow The window to render to
     * @return True if initialization was successful
     */
    virtual bool Initialize(Window& rWindow) = 0;

    /**
     * @brief Begins a new frame for rendering
     */
    virtual void BeginDraw() = 0;

    /**
     * @brief Performs the main draw operations for the current frame
     */
    virtual void Draw() = 0;

    /**
     * @brief Renders all registered sprite components
     */
    virtual void DrawSprites() = 0;

    /**
     * @brief Finalizes the current frame and presents it
     */
    virtual void EndDraw() = 0;

    /**
     * @brief Shuts down the renderer and releases resources
     */
    virtual void Close() = 0;

    /**
     * @brief Gets the type of this renderer implementation
     * @return The renderer type enumeration value
     */
    virtual RendererType GetType() = 0;

    /**
     * @brief Draws a single sprite with specified parameters
     * @param pActor The actor containing transform information
     * @param pTex The texture to render
     * @param pSourceRect Source rectangle within the texture
     * @param pOrigin Origin point for rotation and scaling
     * @param pFlip Flip operation to apply (default: None)
     */
    virtual void DrawSprite(Actor& pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, Flip pFlip = Flip::None) const = 0;

    /**
     * @brief Registers a sprite component for rendering
     * @param pSprite The sprite component to add to the render queue
     */
    virtual void AddSprite(SpriteComponent* pSprite) = 0;

    /**
     * @brief Unregisters a sprite component from rendering
     * @param pSprite The sprite component to remove from the render queue
     */
    virtual void RemoveSprite(SpriteComponent* pSprite) = 0;

    /**
     * @brief Sets the shader program used for sprite rendering
     * @param shaderProgram The shader program to use for sprites
     */
    virtual void SetSpriteShaderProgram(ShaderProgram* shaderProgram) = 0;

    /**
     * @brief Registers a mesh component for rendering
     * @param pMesh The mesh component to add to the render queue
     */
    virtual void AddMesh(MeshComponent* pMesh) = 0;

    /**
     * @brief Unregisters a mesh component from rendering
     * @param pMesh The mesh component to remove from the render queue
     */
    virtual void RemoveMesh(MeshComponent* pMesh) = 0;

    /**
     * @brief Renders all registered mesh components
     */
    virtual void DrawMeshes() = 0;

    /**
     * @brief Sets the view matrix for 3D rendering
     * @param view The view matrix to use for camera transformations
     */
    virtual void SetViewMatrix(Matrix4Row view) = 0;
};
