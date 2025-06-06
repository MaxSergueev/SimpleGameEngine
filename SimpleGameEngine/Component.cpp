#include "Component.h"
#include "Actor.h"

Component::Component(Actor* pOwner, int pUpdateOrder) : mOwner(pOwner), mUpdateOrder(pUpdateOrder)
{
    mOwner->AddComponent(this);
}

Component::~Component()
{
    mOwner->RemoveComponent(this);
}

void Component::OnStart()
{
}

void Component::Update()
{
}

void Component::OnEnd()
{
}
