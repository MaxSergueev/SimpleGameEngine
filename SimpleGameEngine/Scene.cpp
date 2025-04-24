#include "Scene.h"
#include "Actor.h"
#include <algorithm>

#include "Assets.h"
using namespace std;

Scene* Scene::ActiveScene = nullptr;

Scene::Scene( std::string pTitle): mTitle(pTitle), mRenderer(nullptr), mIsUpdatingActors(false)
{
    ActiveScene = this;
}

void Scene::SetRenderer(IRenderer* pRenderer)
{
    mRenderer = pRenderer;
}

void Scene::Unload()
{
    //Free actors pointers memory
    while(!mActors.empty())
    {
        delete mActors.back();
    }
    Assets::Clear();
}

void Scene::AddActor(Actor* actor)
{
    actor->AttachScene(*this);
    if(mIsUpdatingActors){mPendingActors.emplace_back(actor);}
    else mActors.emplace_back(actor);
}

void Scene::RemoveActor(Actor* actor)
{
    vector<Actor*>::iterator it = find(mPendingActors.begin(), mPendingActors.end(), actor);
    if(it != mPendingActors.end())
    {
        iter_swap(it, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }
    it = find(mActors.begin(), mActors.end(), actor);
    if(it != mActors.end())
    {
        iter_swap(it, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Scene::UpdateAllActors()
{
    mIsUpdatingActors = true;
    for(Actor* actor : mActors)
    {
        actor->Update();
    }
    mIsUpdatingActors = false;

    // Add pending actors to the pool
    for(Actor* actor: mPendingActors)
    {
        mActors.emplace_back(actor);
    }
    mPendingActors.clear();
    for(Actor* deadActor: mDeadActors)
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

    // Check all colliders against each other
    for (size_t i = 0; i < mColliders.size(); i++)
    {
        if (!mColliders[i]->IsActive()) continue;

        for (size_t j = i + 1; j < mColliders.size(); j++)
        {
            if (!mColliders[j]->IsActive()) continue;

            AABBColliderComponent* a = mColliders[i];
            AABBColliderComponent* b = mColliders[j];

            // Check if they intersect
            if (a->Intersects(b))
            {
                // Add to current frame collisions
                currentFrameCollisions.push_back(std::make_pair(a, b));

                // Check if this is a new collision
                if (!a->IsCollidingWith(b))
                {
                    // New collision
                    a->OnCollisionEnter(b);
                    b->OnCollisionEnter(a);
                }
                else
                {
                    // Continuing collision
                    a->OnCollisionStay(b);
                    b->OnCollisionStay(a);
                }
            }
        }
    }

    // Check for collisions that ended
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

        // Notify about ended collisions
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
