#include "FPSController.h"
#include "InputManager.h"
#include "Actor.h"
#include <iostream>


FPSController::FPSController(Actor* actor)
    : MoveComponent(actor), mInputX(0), mInputZ(0)
{
}

FPSController::~FPSController()
{
    InputManager::Instance().UnsubscribeTo(SDLK_w, this);
    InputManager::Instance().UnsubscribeTo(SDLK_a, this);
    InputManager::Instance().UnsubscribeTo(SDLK_s, this);
    InputManager::Instance().UnsubscribeTo(SDLK_d, this);
}

void FPSController::OnStart()
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    InputManager::Instance().SubscribeTo(SDLK_w, this);
    InputManager::Instance().SubscribeTo(SDLK_a, this);
    InputManager::Instance().SubscribeTo(SDLK_s, this);
    InputManager::Instance().SubscribeTo(SDLK_d, this);
}

void FPSController::OnNotify(SDL_Event& pEvent)
{
    if (pEvent.type == SDL_KEYDOWN || pEvent.type == SDL_KEYUP)
    {
        if (pEvent.type == SDL_KEYDOWN || pEvent.type == SDL_KEYUP)
        {
            switch (pEvent.key.keysym.sym)
            {
            case SDLK_w:
                mInputZ = (pEvent.type == SDL_KEYDOWN) ? 100.0f : 0.0f;
                break;
            case SDLK_s:
                mInputZ = (pEvent.type == SDL_KEYDOWN) ? -100.0f : 0.0f;
                break;
            case SDLK_a:
                mInputX = (pEvent.type == SDL_KEYDOWN) ? -100.0f : 0.0f;
                break;
            case SDLK_d:
                mInputX = (pEvent.type == SDL_KEYDOWN) ? 100.0f : 0.0f;
                break;
            }

            // Calculate the final speed by combining the input components
            mSpeed = { mInputX, mInputZ };
        }
    }
}