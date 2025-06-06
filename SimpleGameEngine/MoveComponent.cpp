#include "MoveComponent.h"
#include "Maths.h"
#include "Time.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* pOwner, int pUpdateOrder) :
    Component(pOwner, pUpdateOrder), mSpeed(0.0f)
{
}

void MoveComponent::SetSpeed(Vector2 pSpeed)
{
    mSpeed = pSpeed;
}

void MoveComponent::OnStart()
{
}

void MoveComponent::Update()
{
    if (!Maths::NearZero(mSpeed.GetSqrLength()))
    {
        Vector3 newPosition = mOwner->GetTransform().GetPosition()
            + (mOwner->GetTransform().Right() * mSpeed.x
                + mOwner->GetTransform().Forward() * mSpeed.y) * Time::deltaTime;
        mOwner->SetPosition(newPosition);
    }
}
