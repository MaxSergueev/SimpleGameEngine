#pragma once
#include "MoveComponent.h"
#include "IInputListener.h"

class FPSController : public MoveComponent, public IInputListener
{public:
	FPSController() = delete;
	FPSController(const FPSController&) = delete;
	FPSController& operator= (const MoveComponent&) = delete;

	FPSController(Actor* actor);
	~FPSController();

	void OnStart() override;

	// Inherited via IInputListener;
	void OnNotify(SDL_Event& pEvent) override;
private:
	float mInputZ; // Forward
	float mInputX; // Right


};

