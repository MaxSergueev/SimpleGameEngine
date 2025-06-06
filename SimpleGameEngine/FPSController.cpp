#include "FPSController.h"
#include "InputManager.h"
#include "Actor.h"
#include "MoveComponent.h"
#include "FirstPersonActor.h"
#include <iostream>

FPSController::FPSController(Actor* actor)
    : Component(actor), mInputX(0), mInputZ(0), mMoveComponent(nullptr), mFirstPersonActor(nullptr)
{
    mMoveComponent = mOwner->GetComponentOfType<MoveComponent>();

    if (!mMoveComponent) {
        mMoveComponent = new MoveComponent(actor);
    }

    mFirstPersonActor = dynamic_cast<FirstPersonActor*>(actor);
}

void FPSController::OnStart()
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    InputManager::Instance().SubscribeTo(SDLK_w, this);
    InputManager::Instance().SubscribeTo(SDLK_a, this);
    InputManager::Instance().SubscribeTo(SDLK_s, this);
    InputManager::Instance().SubscribeTo(SDLK_d, this);

    InputManager::Instance().SubscribeToMouse(SDL_BUTTON_LEFT, this);
}

FPSController::~FPSController()
{
    InputManager::Instance().UnsubscribeTo(SDLK_w, this);
    InputManager::Instance().UnsubscribeTo(SDLK_a, this);
    InputManager::Instance().UnsubscribeTo(SDLK_s, this);
    InputManager::Instance().UnsubscribeTo(SDLK_d, this);

    InputManager::Instance().UnsubscribeToMouse(SDL_BUTTON_LEFT, this);
}

void FPSController::Update()
{
}

void FPSController::OnNotify(SDL_Event& pEvent)
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

        if (mMoveComponent) {
            mMoveComponent->SetSpeed(Vector2(mInputX, mInputZ));
        }
    }
    else if (pEvent.type == SDL_MOUSEBUTTONDOWN)
    {
        if (pEvent.button.button == SDL_BUTTON_LEFT)
        {
            if (mFirstPersonActor)
            {
                mFirstPersonActor->Shoot();
            }
        }
    }
}
