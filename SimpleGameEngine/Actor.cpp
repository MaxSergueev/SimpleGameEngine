#include "Actor.h"

#include "Component.h"
#include "Scene.h"
using namespace std;

Actor::Actor():mState(ActorState::Active),
mTransform(Transform2D()),
mScene(*Scene::ActiveScene)
{
}

Actor::~Actor()
{
    mScene.RemoveActor(this);
    //Delete every components*
    while(!mComponents.empty())
    {
        delete mComponents.back();
    }
}

Transform2D& Actor::GetTransform()
{
    return mTransform;
}

void Actor::AttachScene(Scene& pScene)
{
    mScene = pScene;
}

void Actor::SetPosition(Vector3 pPosition)
{
    mTransform.SetPosition(pPosition);
}

void Actor::SetScale(Vector3 pScale)
{
    mTransform.SetScale(pScale);
}

void Actor::SetRotation(Quaternion pRotation)
{
    mTransform.SetRotation(pRotation);
}

void Actor::AddComponent(Component* pComponent)
{
    //Find correct place of insertion for the component depending
    //on update order

    int order = pComponent->GetUpdateOrder();
    //std::vector<Component*>::iterator
    auto it = mComponents.begin();
    for(;it != mComponents.end(); ++it)
    {
        if(order < (*it)->GetUpdateOrder()) break;
    }
    mComponents.insert(it, pComponent);
}

void Actor::RemoveComponent(Component* pComponent)
{
    auto it = find(mComponents.begin(), mComponents.end(), pComponent);
    if(it != mComponents.end()) mComponents.erase(it);
}

void Actor::Update()
{
    if(mState != ActorState::Active) return;
    UpdateComponents();
    UpdateActor();
}

void Actor::UpdateComponents()
{
    for(Component* comp : mComponents)
    {
        comp->Update();
    }
}

void Actor::UpdateActor()
{
}


