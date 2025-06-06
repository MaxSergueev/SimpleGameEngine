#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"

/**
 * @brief OpenGL-based renderer implementation for 3D graphics
 *
 * RendererGL provides OpenGL rendering functionality supporting both 2D sprites
 * and 3D meshes. It manages OpenGL context, shader programs, vertex arrays,
 * and view/projection matrices for 3D scene rendering. Implements the IRenderer
 * interface for integration with the engine's rendering system.
 */
class RendererGl : public IRenderer
{
private:
    Window* mWindow;                        ///< Reference to the rendering window
    VertexArray* mSpriteVao;               ///< Vertex array for sprite rendering
    ShaderProgram* mSpriteShaderProgram;   ///< Shader program for 2D sprites
    Matrix4Row mSpriteViewProj;            ///< View-projection matrix for sprites
    Matrix4Row mView;                      ///< View matrix for 3D rendering
    Matrix4Row mProjection;                ///< Projection matrix for 3D rendering
    SDL_GLContext mContext;                ///< OpenGL rendering context
    std::vector<SpriteComponent*> mSprites; ///< Collection of sprites to render
    std::vector<MeshComponent*> mMeshes;   ///< Collection of meshes to render

public:
    /**
     * @brief Default constructor - initializes matrices and default values
     */
    RendererGl();

    /**
     * @brief Virtual destructor - cleans up OpenGL resources
     */
    virtual ~RendererGl();

    RendererGl(const RendererGl&) = delete;
    RendererGl& operator=(const RendererGl&) = delete;

    /**
     * @brief Initializes OpenGL context and rendering resources
     * @param rWindow The window to create the OpenGL context for
     * @return True if initialization was successful
     */
    bool Initialize(Window& rWindow) override;

    /**
     * @brief Begins a new rendering frame
     */
    void BeginDraw() override;

    /**
     * @brief Renders all registered meshes and sprites
     */
    void Draw() override;

    /**
     * @brief Renders a single sprite with specified parameters
     * @param pActor The actor containing transform information
     * @param pTex The texture to render
     * @param pSourceRect Source rectangle within the texture
     * @param pOrigin Origin point for rotation and scaling
     * @param pFlip Flip operation to apply (default: None)
     */
    void DrawSprite(Actor& pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, Flip pFlip = Flip::None) const override;

    /**
     * @brief Finalizes the current frame and swaps buffers
     */
    void EndDraw() override;

    /**
     * @brief Shuts down the renderer and releases OpenGL resources
     */
    void Close() override;

    /**
     * @brief Gets the renderer type identifier
     * @return RendererType::OPENGL
     */
    RendererType GetType() override;

    /**
     * @brief Sets the shader program used for sprite rendering
     * @param shaderProgram The shader program to use for 2D sprites
     */
    void SetSpriteShaderProgram(ShaderProgram* shaderProgram);

    /**
     * @brief Renders all registered sprite components
     */
    void DrawSprites() override;

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
     * @brief Registers a mesh component for rendering
     * @param pMesh The mesh component to add to the render queue
     */
    void AddMesh(MeshComponent* pMesh) override;

    /**
     * @brief Unregisters a mesh component from rendering
     * @param pMesh The mesh component to remove from the render queue
     */
    void RemoveMesh(MeshComponent* pMesh) override;

    /**
     * @brief Renders all registered mesh components
     */
    void DrawMeshes() override;

    /**
     * @brief Sets the view matrix for 3D camera transformations
     * @param view The view matrix to use for 3D rendering
     */
    void SetViewMatrix(Matrix4Row view) override;
};
