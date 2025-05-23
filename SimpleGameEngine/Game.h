#pragma once
#include <string>
#include <vector>

#include "IRenderer.h"
#include "Scene.h"
#include "Window.h"
#include "InputManager.h"


class Game
{
private:
    std::string mTitle;
    Window* mWindow;
    IRenderer* mRenderer;
    InputManager* mInputManager;

    bool mIsRunning;
    std::vector<Scene*> mScenes;
    int mLoadedScene;
public:
    Game(std::string pTitle = "Game", std::vector<Scene*> pScenes = {}, IRenderer::RendererType pType = IRenderer::RendererType::OPENGL);
    ~Game();

    void Initialize();
    void Loop();
    void Render();
    void Close();

private:
    void CheckInputs();
};
