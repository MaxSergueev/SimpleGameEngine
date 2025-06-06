#include "Game.h"
#include <iostream>
#include <SDL.h>
#include "RendererSDL.h"
#include "RendererGL.h"

#include "Log.h"
#include "Time.h"
#include "Scenes/Pong.h"
class Scene;
using namespace std;

Game::Game(std::string pTitle, std::vector<Scene*> pScenes, IRenderer::RendererType pType)
    : mTitle(pTitle), mIsRunning(true), mScenes(std::move(pScenes)), mLoadedScene(0)
{
    if (pType == IRenderer::RendererType::SDL) {
        mRenderer = new RendererSDL();
    }
    else if (pType == IRenderer::RendererType::OPENGL) {
        mRenderer = new RendererGl();
    }

    if (mScenes.empty())
    {
        Log::Error(LogType::Error, "No scene set for game");
    }
    for (vector<Scene*>::iterator s = mScenes.begin(); s != mScenes.end(); ++s)
    {
        (*s)->SetRenderer(mRenderer);
    }
}

Game::~Game()
{
    delete mWindow;
}

void Game::Initialize()
{
    mWindow = new Window(1584, 891);

    mInputManager = new InputManager;

    if (mWindow->Open() && mRenderer->Initialize(*mWindow))
    {
        mScenes[mLoadedScene]->Start();
        mScenes[mLoadedScene]->Load();
        Loop();
    }
}

void Game::Loop()
{
    while (mIsRunning)
    {
        Time::ComputeDeltaTime();
        CheckInputs();
        mScenes[mLoadedScene]->UpdateAllActors();
        mScenes[mLoadedScene]->Update();
        Render();
        Time::DelayTime();
    }
    Close();
}

void Game::Render()
{
    mRenderer->BeginDraw();
    mRenderer->Draw();
    mRenderer->EndDraw();
}

void Game::CheckInputs()
{
    if (mIsRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    mIsRunning = false;
                }
            default:
                InputManager::Instance().HandleInputs(event);
                break;
            }
        }
    }
}

void Game::Close()
{
    mScenes[mLoadedScene]->Unload();
    if (!mScenes.empty())mScenes[mLoadedScene]->Close();
    mRenderer->Close();
    mWindow->Close();
    SDL_Quit();
}