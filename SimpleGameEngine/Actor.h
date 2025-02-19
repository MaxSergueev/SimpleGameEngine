#pragma once
#include <vector>

#include "Transform2D.h"

class Scene;
class Component;

class Actor
{
public:
    enum class ActorState
    {
        Active,
        Paused,
        Dead
    };
protected:
    Scene& mScene;
    ActorState mState;
    Transform2D mTransform;
    std::vector<Component*> mComponents;
public:
    
    Actor();
    virtual ~Actor();
    Actor(const Actor&) = delete;
    Actor& operator=(const Actor&) = delete;
    ActorState GetState() const {return mState;}

    Scene& GetScene() const {return mScene;}
    Transform2D& GetTransform();

    void AttachScene(Scene& pScene);
    void SetPosition(Vector2 pPosition);
    void SetScale(Vector2 pScale);
    void SetRotation(float pRotation);

    virtual void Start(){}
    void AddComponent(Component* pComponent);
    void RemoveComponent(Component* pComponent);
    void Update();
    void UpdateComponents();
    virtual void UpdateActor();
    void SetActive(bool pActive = true) {mState = pActive? ActorState::Active : ActorState::Paused;}
    void Destroy(){mState = ActorState::Dead;}
    
};
