#pragma once
#include <vector>

#include "Transform2D.h"
#include "Component.h"

class Scene;

class Actor
{
public:
    enum class ActorState
    {
        Active,
        Paused,
        Dead
    };

    template<typename  C>
    C* GetComponentOfType() const
    {
        C* result = nullptr;
        for (Component* component : mComponents)
        {
            result = dynamic_cast<C*>(component);
            if (result != nullptr) return result;
        }
        return nullptr;
    }


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
    void SetPosition(Vector3 pPosition);
    void SetScale(Vector3 pScale);
    void SetRotation(Vector3 pRotation);

    void Rotate(Vector3 pRotation);
    void RotateAroundAxis(Vector3 pAxis, float pAngle);
    void RotateX(float pRotation);
    void RotateY(float pRotation);
    void RotateZ(float pRotation);

    virtual void Start(){}
    void AddComponent(Component* pComponent);
    void RemoveComponent(Component* pComponent);
    void Update();
    void UpdateComponents();
    virtual void UpdateActor();
    void SetActive(bool pActive = true) {mState = pActive? ActorState::Active : ActorState::Paused;}
    void Destroy(){mState = ActorState::Dead;}
    
};
