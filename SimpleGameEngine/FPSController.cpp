#include "FPSController.h"
#include "InputManager.h"
#include "Actor.h"
#include "MoveComponent.h"
#include "FirstPersonActor.h"
#include <iostream>

FPSController::FPSController(Actor* actor)
    : Component(actor), mInputX(0), mInputZ(0), mMoveComponent(nullptr), mFirstPersonActor(nullptr)
{
    // Find the MoveComponent on the actor
    mMoveComponent = mOwner->GetComponentOfType<MoveComponent>();

    // If no MoveComponent exists, create one
    if (!mMoveComponent) {
        mMoveComponent = new MoveComponent(actor);
    }

    // Try to cast the actor to FirstPersonActor for shooting functionality
    mFirstPersonActor = dynamic_cast<FirstPersonActor*>(actor);
}

void FPSController::OnStart()
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
    InputManager::Instance().SubscribeTo(SDLK_w, this);
    InputManager::Instance().SubscribeTo(SDLK_a, this);
    InputManager::Instance().SubscribeTo(SDLK_s, this);
    InputManager::Instance().SubscribeTo(SDLK_d, this);

    // Subscribe to left mouse button
    InputManager::Instance().SubscribeToMouse(SDL_BUTTON_LEFT, this);
}

FPSController::~FPSController()
{
    InputManager::Instance().UnsubscribeTo(SDLK_w, this);
    InputManager::Instance().UnsubscribeTo(SDLK_a, this);
    InputManager::Instance().UnsubscribeTo(SDLK_s, this);
    InputManager::Instance().UnsubscribeTo(SDLK_d, this);

    // Unsubscribe from mouse button
    InputManager::Instance().UnsubscribeToMouse(SDL_BUTTON_LEFT, this);
}

void FPSController::Update()
{
}

void FPSController::OnNotify(SDL_Event& pEvent)
{
    // Handle keyboard input for movement
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

        // Calculate the final speed and set it on the MoveComponent
        if (mMoveComponent) {
            mMoveComponent->SetSpeed(Vector2(mInputX, mInputZ));
        }
    }

    // Handle mouse clicks for shooting
    else if (pEvent.type == SDL_MOUSEBUTTONDOWN)
    {
        if (pEvent.button.button == SDL_BUTTON_LEFT) // Left mouse button
        {
            if (mFirstPersonActor)
            {
                mFirstPersonActor->Shoot();
            }
        }
    }
}

