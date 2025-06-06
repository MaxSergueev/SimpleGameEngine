#include "Scene.h"
#include "Actor.h"
#include <algorithm>

#include "Assets.h"
using namespace std;

Scene* Scene::ActiveScene = nullptr;

Scene::Scene(std::string pTitle) : mTitle(pTitle), mRenderer(nullptr), mIsUpdatingActors(false)
{
    ActiveScene = this;
}

void Scene::SetRenderer(IRenderer* pRenderer)
{
    mRenderer = pRenderer;
}

void Scene::Unload()
{
    while (!mActors.empty())
    {
        delete mActors.back();
        mActors.pop_back();
    }
    Assets::Clear();
}

void Scene::AddActor(Actor* actor)
{
    actor->AttachScene(*this);
    if (mIsUpdatingActors) { mPendingActors.emplace_back(actor); }
    else mActors.emplace_back(actor);
}

void Scene::RemoveActor(Actor* actor)
{
    vector<Actor*>::iterator it = find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (it != mPendingActors.end())
    {
        iter_swap(it, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }
    it = find(mActors.begin(), mActors.end(), actor);
    if (it != mActors.end())
    {
        iter_swap(it, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Scene::UpdateAllActors()
{
    mIsUpdatingActors = true;
    for (Actor* actor : mActors)
    {
        actor->Update();
    }
    mIsUpdatingActors = false;

    for (Actor* actor : mPendingActors)
    {
        mActors.emplace_back(actor);
    }
    mPendingActors.clear();
    for (Actor* deadActor : mDeadActors)
    {
        delete deadActor;
    }
}

void Scene::AddCollider(AABBColliderComponent* collider)
{
    mColliders.push_back(collider);
}

void Scene::RemoveCollider(AABBColliderComponent* collider)
{
    auto iter = std::find(mColliders.begin(), mColliders.end(), collider);
    if (iter != mColliders.end())
    {
        mColliders.erase(iter);
    }
}

void Scene::CheckCollisions()
{
    std::vector<std::pair<AABBColliderComponent*, AABBColliderComponent*>> currentFrameCollisions;

    for (size_t i = 0; i < mColliders.size(); i++)
    {
        if (!mColliders[i]->IsActive()) continue;

        for (size_t j = i + 1; j < mColliders.size(); j++)
        {
            if (!mColliders[j]->IsActive()) continue;

            AABBColliderComponent* a = mColliders[i];
            AABBColliderComponent* b = mColliders[j];

            if (a->Intersects(b))
            {
                currentFrameCollisions.push_back(std::make_pair(a, b));

                if (!a->IsCollidingWith(b))
                {
                    a->OnCollisionEnter(b);
                    b->OnCollisionEnter(a);
                }
                else
                {
                    a->OnCollisionStay(b);
                    b->OnCollisionStay(a);
                }
            }
        }
    }

    for (auto& collider : mColliders)
    {
        if (!collider->IsActive()) continue;

        const auto& currentCollisions = collider->GetCurrentCollisions();
        std::vector<AABBColliderComponent*> endedCollisions;

        for (auto& collision : currentCollisions)
        {
            bool stillColliding = false;

            for (auto& currentCollision : currentFrameCollisions)
            {
                if ((currentCollision.first == collider && currentCollision.second == collision) ||
                    (currentCollision.second == collider && currentCollision.first == collision))
                {
                    stillColliding = true;
                    break;
                }
            }

            if (!stillColliding)
            {
                endedCollisions.push_back(collision);
            }
        }

        for (auto& ended : endedCollisions)
        {
            collider->OnCollisionExit(ended);
        }
    }
}

IRenderer& Scene::GetRenderer()
{
    return *mRenderer;
}
