#include "PinPhysicsComponent.h"
#include "Actor.h"
#include <cmath>

PinPhysicsComponent::PinPhysicsComponent(Actor* owner)
    : Component(owner), mFrictionFactor(0.95f)
{
    mMoveComponent = owner->GetComponentOfType<MoveComponent>();
    if (!mMoveComponent)
    {
    }
}

void PinPhysicsComponent::Update()
{
    if (mMoveComponent)
    {
        Vector2 currentSpeed = mMoveComponent->GetSpeed();

        float speedMagnitude = sqrt(currentSpeed.GetSqrLength());

        if (speedMagnitude > 0.1f)
        {
            float dynamicFriction = mFrictionFactor;
            if (speedMagnitude > 10.0f) {
                dynamicFriction = 0.99f;
            }
            else if (speedMagnitude > 5.0f) {
                dynamicFriction = 0.98f;
            }

            Vector2 newSpeed = currentSpeed * dynamicFriction;

            if (sqrt(newSpeed.GetSqrLength()) < 0.1f)
            {
                newSpeed = Vector2(0.0f, 0.0f);
            }

            mMoveComponent->SetSpeed(newSpeed);
        }
        else if (speedMagnitude > 0.0f)
        {
            mMoveComponent->SetSpeed(Vector2(0.0f, 0.0f));
        }
    }
}
