#pragma once
#include <vector>
#include "Transform2D.h"
#include "Component.h"

class Scene;

/**
 * @brief Base class for all game objects in the engine
 *
 * Actor represents any entity in the game world that can have components,
 * a transform, and can be updated each frame. Actors manage their own
 * components and provide a template-based system for component retrieval.
 */
class Actor
{
public:
    /**
     * @brief Possible states for an actor
     */
    enum class ActorState
    {
        Active,  ///< Actor is active and updating
        Paused,  ///< Actor is paused and not updating
        Dead     ///< Actor is marked for destruction
    };

    /**
     * @brief Gets the first component of the specified type
     * @tparam C The component type to search for
     * @return Pointer to the component if found, nullptr otherwise
     */
    template<typename C>
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
    Scene& mScene;                          ///< Reference to the scene containing this actor
    ActorState mState;                      ///< Current state of the actor
    Transform2D mTransform;                 ///< Transform component for position, rotation, scale
    std::vector<Component*> mComponents;    ///< List of components attached to this actor

public:
    /**
     * @brief Default constructor
     */
    Actor();

    /**
     * @brief Virtual destructor - cleans up components and removes from scene
     */
    virtual ~Actor();

    Actor(const Actor&) = delete;
    Actor& operator=(const Actor&) = delete;

    /**
     * @brief Gets the current state of the actor
     * @return The current ActorState
     */
    ActorState GetState() const { return mState; }

    /**
     * @brief Gets the scene containing this actor
     * @return Reference to the containing scene
     */
    Scene& GetScene() const { return mScene; }

    /**
     * @brief Gets the actor's transform component
     * @return Reference to the transform
     */
    Transform2D& GetTransform();

    /**
     * @brief Gets the world transform matrix
     * @return The world transformation matrix
     */
    Matrix4Row GetWorldTransform() const { return mTransform.GetWorldTransform(); }

    /**
     * @brief Attaches this actor to a scene
     * @param pScene The scene to attach to
     */
    void AttachScene(Scene& pScene);

    /**
     * @brief Sets the actor's world position
     * @param pPosition The new position
     */
    void SetPosition(Vector3 pPosition);

    /**
     * @brief Sets the actor's scale
     * @param pScale The new scale
     */
    void SetScale(Vector3 pScale);

    /**
     * @brief Sets the actor's rotation
     * @param pRotation The new rotation
     */
    void SetRotation(Vector3 pRotation);

    /**
     * @brief Rotates the actor by the specified amount
     * @param pRotation The rotation to apply
     */
    void Rotate(Vector3 pRotation);

    /**
     * @brief Rotates the actor around a specific axis
     * @param pAxis The axis to rotate around
     * @param pAngle The angle to rotate in radians
     */
    void RotateAroundAxis(Vector3 pAxis, float pAngle);

    /**
     * @brief Rotates the actor around the X axis
     * @param pRotation The rotation amount in radians
     */
    void RotateX(float pRotation);

    /**
     * @brief Rotates the actor around the Y axis
     * @param pRotation The rotation amount in radians
     */
    void RotateY(float pRotation);

    /**
     * @brief Rotates the actor around the Z axis
     * @param pRotation The rotation amount in radians
     */
    void RotateZ(float pRotation);

    /**
     * @brief Called when the actor is first created - override for initialization
     */
    virtual void Start() {}

    /**
     * @brief Adds a component to this actor
     * @param pComponent The component to add
     */
    void AddComponent(Component* pComponent);

    /**
     * @brief Removes a component from this actor
     * @param pComponent The component to remove
     */
    void RemoveComponent(Component* pComponent);

    /**
     * @brief Updates the actor and all its components
     */
    void Update();

    /**
     * @brief Updates all components attached to this actor
     */
    void UpdateComponents();

    /**
     * @brief Actor-specific update logic - override in derived classes
     */
    virtual void UpdateActor();

    /**
     * @brief Sets the actor's active state
     * @param pActive True to activate, false to pause
     */
    void SetActive(bool pActive = true) { mState = pActive ? ActorState::Active : ActorState::Paused; }

    /**
     * @brief Marks the actor for destruction
     */
    void Destroy() { mState = ActorState::Dead; }
};

