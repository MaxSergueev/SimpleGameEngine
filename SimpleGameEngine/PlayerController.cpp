#include "PlayerController.h"
#include "InputManager.h"
#include "Actor.h"
#include <iostream>
#include "SpriteComponent.h"

PlayerController::PlayerController(Actor* actor)
    : MoveComponent(actor), mInputX(0), mInputY(0)
{
}

PlayerController::~PlayerController()
{
	InputManager::Instance().UnsubscribeTo(SDLK_w, this);
    InputManager::Instance().UnsubscribeTo(SDLK_a, this);
    InputManager::Instance().UnsubscribeTo(SDLK_s, this);
    InputManager::Instance().UnsubscribeTo(SDLK_d, this);
}

void PlayerController::OnStart()
{
	InputManager::Instance().SubscribeTo(SDLK_w, this);
	InputManager::Instance().SubscribeTo(SDLK_a, this);
	InputManager::Instance().SubscribeTo(SDLK_s, this);
	InputManager::Instance().SubscribeTo(SDLK_d, this);
}

void PlayerController::OnNotify(SDL_Event& pEvent)
{
 if (pEvent.type == SDL_KEYDOWN || pEvent.type == SDL_KEYUP)
    {
     if (pEvent.type == SDL_KEYDOWN || pEvent.type == SDL_KEYUP)
     {
         switch (pEvent.key.keysym.sym)
         {
         case SDLK_w:
             mInputY = (pEvent.type == SDL_KEYDOWN) ? 30.0f : 0.0f;
             break;
         case SDLK_s:
             mInputY = (pEvent.type == SDL_KEYDOWN) ? -30.0f : 0.0f;
             break;
         case SDLK_a:
             mOwner->GetComponentOfType<SpriteComponent>()->SetFlipX(true);
             mInputX = (pEvent.type == SDL_KEYDOWN) ? -30.0f : 0.0f;
             break;
         case SDLK_d:
             mOwner->GetComponentOfType<SpriteComponent>()->SetFlipX(false);
             mInputX = (pEvent.type == SDL_KEYDOWN) ? 30.0f : 0.0f;
             break;
         }

         // Calculate the final speed by combining the input components
         mSpeed = { mInputX, mInputY };
     }
    }
}
