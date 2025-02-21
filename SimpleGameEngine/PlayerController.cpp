#include "PlayerController.h"
#include "InputManager.h"

PlayerController::~PlayerController()
{
	InputManager::Instance().UnsubscribeTo(SDLK_SPACE, this);
}

void PlayerController::OnStart()
{
	InputManager::Instance().SubscribeTo(SDLK_SPACE, this);
}

void PlayerController::OnNotify(SDL_Event& pEvent)
{

}