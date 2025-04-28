#include "PinPhysicsComponent.h"
#include "Actor.h"
#include <cmath>

PinPhysicsComponent::PinPhysicsComponent(Actor* owner)
    : Component(owner), mFrictionFactor(0.95f)
{
    // Find the MoveComponent on the owner
    mMoveComponent = owner->GetComponentOfType<MoveComponent>();
    if (!mMoveComponent)
    {
        // Log error here
    }
}

void PinPhysicsComponent::Update()
{
    if (mMoveComponent)
    {
        // Get current speed
        Vector2 currentSpeed = mMoveComponent->GetSpeed();

        // Calculate speed magnitude
        float speedMagnitude = sqrt(currentSpeed.GetSqrLength());

        // Only apply friction if the pin is moving
        if (speedMagnitude > 0.1f)
        {
            // Calculate dynamic friction factor - less friction at high speeds
            float dynamicFriction = mFrictionFactor;
            if (speedMagnitude > 10.0f) {
                // Apply even less friction at high speeds (closer to 1.0)
                dynamicFriction = 0.99f;
            }
            else if (speedMagnitude > 5.0f) {
                // Medium speed, medium friction
                dynamicFriction = 0.98f;
            }

            // Apply friction
            Vector2 newSpeed = currentSpeed * dynamicFriction;

            // If speed is very small, just stop the pin
            if (sqrt(newSpeed.GetSqrLength()) < 0.1f)
            {
                newSpeed = Vector2(0.0f, 0.0f);
            }

            // Set the new speed
            mMoveComponent->SetSpeed(newSpeed);
        }
        else if (speedMagnitude > 0.0f)
        {
            // If speed is low, stop completely
            mMoveComponent->SetSpeed(Vector2(0.0f, 0.0f));
        }
    }
}

