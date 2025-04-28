#include "Pin.h"
#include "Assets.h"
#include "Scene.h"
#include "BowlingBall.h"
#include <cmath>

Pin::Pin(Scene* scene, const Vector3& position)
    : mIsKnocked(false), mMass(0.1f)
{
    scene->AddActor(this);

    SetPosition(position);
    SetRotation(Vector3(0, 0, 0));
    SetScale(Vector3(2.5f, 2.5f, 2.5f));

    mMeshComponent = new MeshComponent(this);
    mMeshComponent->SetMesh(Assets::GetMesh("pin"));
    mMeshComponent->GetMesh()->SetTexture(&Assets::GetTexture("pin"));

    mMoveComponent = new MoveComponent(this);
    mMoveComponent->SetSpeed(Vector2(0.0f, 0.0f));

    mColliderComponent = new AABBColliderComponent(this);
    mColliderComponent->SetDimensions(Vector3(7.5f, 10.0f, 7.5f));

    mPhysicsComponent = new PinPhysicsComponent(this);
    mPhysicsComponent->SetFrictionFactor(0.95f);

    SetupCollisionCallbacks();
}

void Pin::SetupCollisionCallbacks()
{
    mColliderComponent->SetOnCollisionEnter([this](AABBColliderComponent* other) {
        // Check if collision is with a bowling ball
        BowlingBall* ball = dynamic_cast<BowlingBall*>(other->GetOwner());
        if (ball) {
            // Get ball's velocity and calculate impact
            Vector2 ballVelocity = ball->GetMoveComponent()->GetSpeed();
            float ballSpeed = sqrt(ballVelocity.GetSqrLength());

            // Calculate direction from ball to pin
            Vector3 ballPos = ball->GetTransform().GetPosition();
            Vector3 pinPos = this->GetTransform().GetPosition();
            Vector2 direction(pinPos.x - ballPos.x, pinPos.z - ballPos.z);

            // Normalize direction if not zero
            float dirLength = sqrt(direction.GetSqrLength());
            if (dirLength > 0.001f) {
                direction.x /= dirLength;
                direction.y /= dirLength;
            }
            else {
                // Default direction if pin and ball are at same position
                direction = Vector2(0.0f, 1.0f);
            }

            // Apply impulse based on ball's speed and mass
            float force = ballSpeed * ball->GetMass() / mMass;
            ApplyImpulse(direction, force);

            // Mark pin as knocked
            mIsKnocked = true;
        }

        // Check if collision is with another pin
        Pin* otherPin = dynamic_cast<Pin*>(other->GetOwner());
        if (otherPin && otherPin->IsKnocked()) {
            // Get other pin's velocity
            Vector2 otherVelocity = otherPin->GetMoveComponent()->GetSpeed();
            float otherSpeed = sqrt(otherVelocity.GetSqrLength());

            // Only react if the other pin is moving with some speed
            if (otherSpeed > 0.1f) {
                // Calculate direction from other pin to this pin
                Vector3 otherPos = otherPin->GetTransform().GetPosition();
                Vector3 thisPos = this->GetTransform().GetPosition();
                Vector2 direction(thisPos.x - otherPos.x, thisPos.z - otherPos.z);

                // Normalize direction if not zero
                float dirLength = sqrt(direction.GetSqrLength());
                if (dirLength > 0.001f) {
                    direction.x /= dirLength;
                    direction.y /= dirLength;
                }
                else {
                    // Default direction if pins are at same position
                    direction = Vector2(0.0f, 1.0f);
                }

                // Apply impulse based on other pin's speed and mass ratio
                float force = otherSpeed * otherPin->GetMass() / mMass * 0.8f;
                ApplyImpulse(direction, force);

                // Mark pin as knocked
                mIsKnocked = true;
            }
        }
        });
}

void Pin::ApplyImpulse(const Vector2& direction, float force)
{
    // Calculate resulting velocity
    Vector2 currentVelocity = mMoveComponent->GetSpeed();
    Vector2 addedVelocity = direction * force;

    // Apply the new velocity
    Vector2 newVelocity = currentVelocity + addedVelocity;

    float maxSpeed = 50.0f;
    float currentSpeed = sqrt(newVelocity.GetSqrLength());
    if (currentSpeed > maxSpeed) {
        newVelocity.x = (newVelocity.x / currentSpeed) * maxSpeed;
        newVelocity.y = (newVelocity.y / currentSpeed) * maxSpeed;
    }

    mMoveComponent->SetSpeed(newVelocity);
}

