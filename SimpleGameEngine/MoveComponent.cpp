#include "MoveComponent.h"
#include "Maths.h"
#include "Time.h"
#include "Actor.h"

#include "InputManager.h"



MoveComponent::MoveComponent(Actor* pOwner, int pUpdateOrder) :
    Component(pOwner, pUpdateOrder), mSpeed(0.0f)
{
}

MoveComponent::~MoveComponent()
{
    //UNSUB
}

void MoveComponent::SetSpeed(Vector2 pSpeed)
{
    mSpeed = pSpeed;
}

void MoveComponent::OnStart()
{
    InputManager::Instance().SubscribeTo(SDLK_SPACE, this);
}

void MoveComponent::Update()
{
    if (!Maths::NearZero(mSpeed.GetSqrLength()))
    {
        Vector2 newPosition = mOwner->GetTransform().GetPosition()
            + (mOwner->GetTransform().Right() * mSpeed.x
                + mOwner->GetTransform().Up() * mSpeed.y) * Time::deltaTime;
        mOwner->SetPosition(newPosition);
    }
}

void MoveComponent::OnNotify(SDL_Event& pEvent)
{

}
