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

void Scene::SetRenderer(Renderer* pRenderer)
{
    mRenderer = pRenderer;
}

void Scene::Unload()
{
    //Free actors pointers memory
    //Because ~Actor() calls RemoveActor, we have to use a while loop
    while(!mActors.empty())
    {
        delete mActors.back();
    }
    //Free up resources
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

Renderer& Scene::GetRenderer()
{
    return *mRenderer;
}
