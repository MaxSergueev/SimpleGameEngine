#pragma once
#include <SDL_events.h>
#include <string>
#include <vector>

#include "RendererSDL.h"
#include "AABBColliderComponent.h"

class Actor;

class Scene
{
private:
    std::vector<AABBColliderComponent*> mColliders;

protected:
    std::string mTitle;
    IRenderer* mRenderer;
    bool mIsUpdatingActors;
    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;
    std::vector<Actor*> mDeadActors;
public:

    static Scene* ActiveScene;
    
    virtual ~Scene() = default;
    Scene(std::string pTitle = "Base Scene");
    void SetRenderer(IRenderer* pRenderer);
    virtual void Start() = 0;
    virtual void Render()= 0;
    virtual void Update()=0;
                            //virtual void OnInputs(SDL_Event pEvent)= 0;
    virtual void Close() = 0;

    // Assets Management
    virtual void Load(){}
    virtual void Unload();

    // Actors Management
    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);
    void UpdateAllActors();

	// Colliders Management
    void AddCollider(AABBColliderComponent* collider);
    void RemoveCollider(AABBColliderComponent* collider);
    void CheckCollisions();

    // Getters
    const std::vector<AABBColliderComponent*>& GetColliders() const { return mColliders; };
    const std::vector<Actor*>& GetActors() const { return mActors; }

    
    IRenderer& GetRenderer();
};
