#pragma once
#include "Component.h"
#include "Vector2.h"

class MoveComponent : public Component
{
protected:
	Vector2 mSpeed;
public:
	MoveComponent(Actor* pOwner, int pUpdateOrder = 100);
	MoveComponent() = delete;
	MoveComponent(const MoveComponent&) = delete;
	MoveComponent& operator= (const MoveComponent&) = delete;

	Vector2 GetSpeed() const { return mSpeed; }
	void SetSpeed(Vector2 pSpeed);

	void Update() override;
};
