#pragma once
#include <string>
#include <vector>

#include "IRenderer.h"
#include "Scene.h"
#include "Window.h"
#include "InputManager.h"

/**
 * @brief Main game class that manages the core game loop and systems
 *
 * Game handles initialization, the main game loop, rendering, input processing,
 * and cleanup. It manages multiple scenes and coordinates between the window,
 * renderer, and input systems.
 */
class Game
{
private:
    std::string mTitle;                 ///< Window title for the game
    Window* mWindow;                    ///< Game window instance
    IRenderer* mRenderer;               ///< Rendering system interface
    InputManager* mInputManager;        ///< Input handling system

    bool mIsRunning;                    ///< Whether the game loop should continue
    std::vector<Scene*> mScenes;        ///< Collection of game scenes
    int mLoadedScene;                   ///< Index of currently active scene

public:
    /**
     * @brief Constructs a game with specified parameters
     * @param pTitle Window title (default: "Game")
     * @param pScenes Vector of scenes to manage (default: empty)
     * @param pType Renderer type to use (default: OpenGL)
     */
    Game(std::string pTitle = "Game", std::vector<Scene*> pScenes = {}, IRenderer::RendererType pType = IRenderer::RendererType::OPENGL);

    /**
     * @brief Destructor - cleans up window resources
     */
    ~Game();

    /**
     * @brief Initializes all game systems and starts the main loop
     */
    void Initialize();

    /**
     * @brief Main game loop - handles updates and rendering
     */
    void Loop();

    /**
     * @brief Renders the current frame
     */
    void Render();

    /**
     * @brief Shuts down all game systems and cleans up resources
     */
    void Close();

private:
    /**
     * @brief Processes input events and handles quit conditions
     */
    void CheckInputs();
};
