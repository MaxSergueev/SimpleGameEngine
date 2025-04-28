#pragma once
#include "Component.h"
#include "MoveComponent.h"

class PinPhysicsComponent : public Component
{
private:
    MoveComponent* mMoveComponent;
    float mFrictionFactor;

public:
    PinPhysicsComponent(class Actor* owner);
    ~PinPhysicsComponent() = default;

    void Update() override;
    void SetFrictionFactor(float factor) { mFrictionFactor = factor; }
    float GetFrictionFactor() const { return mFrictionFactor; }
};


