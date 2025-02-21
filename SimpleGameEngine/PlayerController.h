#pragma once
#include "MoveComponent.h"
#include "IInputListener.h"

class PlayerController : public MoveComponent, public IInputListener
{public:
	PlayerController() = delete;
	PlayerController(const PlayerController&) = delete;
	PlayerController& operator= (const MoveComponent&) = delete;

	~PlayerController();

	void OnStart() override;

	// Inherited via IInputListener
	void OnNotify(SDL_Event& pEvent) override;
};

