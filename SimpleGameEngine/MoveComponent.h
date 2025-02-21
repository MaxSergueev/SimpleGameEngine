#pragma once
#include "Component.h"
#include "Vector2.h"
#include "IInputListener.h"

class MoveComponent : public Component, public IInputListener
{
protected:
	Vector2 mSpeed;
public:
	MoveComponent(Actor* pOwner, int pUpdateOrder = 100);
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator= (const MoveComponent&) = delete;

	~MoveComponent();

	Vector2 GetSpeed() const { return mSpeed; }
	void SetSpeed(Vector2 pSpeed);

	void OnStart() override;
	void Update() override;

	// Inherited via IInputListener
	void OnNotify(SDL_Event& pEvent) override;
};
