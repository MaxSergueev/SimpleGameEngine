#pragma once
#include <SDL_events.h>
#include <string>
#include <vector>

#include "RendererSDL.h"
#include "AABBColliderComponent.h"

class Actor;

/**
 * @brief Base class for game scenes that manage actors, rendering, and collision detection
 *
 * Scene provides the foundation for game states, managing collections of actors,
 * collision detection between AABB colliders, and integration with the rendering
 * system. It handles actor lifecycle management with pending/dead actor queues
 * to safely manage objects during update cycles.
 */
class Scene
{
private:
    std::vector<AABBColliderComponent*> mColliders; ///< Collection of all active colliders in the scene

protected:
    std::string mTitle;                     ///< Scene title/identifier
    IRenderer* mRenderer;                   ///< Renderer interface for drawing operations
    bool mIsUpdatingActors;                 ///< Flag to prevent actor modification during updates
    std::vector<Actor*> mActors;            ///< Collection of active actors in the scene
    std::vector<Actor*> mPendingActors;     ///< Actors waiting to be added to the main collection
    std::vector<Actor*> mDeadActors;        ///< Actors marked for deletion

public:
    static Scene* ActiveScene;  ///< Global pointer to the currently active scene

    /**
     * @brief Virtual destructor for proper inheritance cleanup
     */
    virtual ~Scene() = default;

    /**
     * @brief Constructs a scene with the specified title
     * @param pTitle The name/identifier for this scene (default: "Base Scene")
     */
    Scene(std::string pTitle = "Base Scene");

    /**
     * @brief Sets the renderer interface for this scene
     * @param pRenderer Pointer to the renderer implementation to use
     */
    void SetRenderer(IRenderer* pRenderer);

    /**
     * @brief Called when the scene becomes active - must be implemented by derived classes
     */
    virtual void Start() = 0;

    /**
     * @brief Called each frame to render the scene - must be implemented by derived classes
     */
    virtual void Render() = 0;

    /**
     * @brief Called each frame to update scene logic - must be implemented by derived classes
     */
    virtual void Update() = 0;

    /**
     * @brief Called when the scene is being shut down - must be implemented by derived classes
     */
    virtual void Close() = 0;

    /**
     * @brief Loads scene assets and resources (optional override)
     */
    virtual void Load() {}

    /**
     * @brief Unloads scene assets and cleans up all actors
     */
    virtual void Unload();

    /**
     * @brief Adds an actor to the scene
     * @param actor Pointer to the actor to add
     */
    void AddActor(Actor* actor);

    /**
     * @brief Removes an actor from the scene
     * @param actor Pointer to the actor to remove
     */
    void RemoveActor(Actor* actor);

    /**
     * @brief Updates all actors and processes pending additions/deletions
     */
    void UpdateAllActors();

    /**
     * @brief Registers a collider component for collision detection
     * @param collider Pointer to the collider to add to the collision system
     */
    void AddCollider(AABBColliderComponent* collider);

    /**
     * @brief Unregisters a collider component from collision detection
     * @param collider Pointer to the collider to remove from the collision system
     */
    void RemoveCollider(AABBColliderComponent* collider);

    /**
     * @brief Performs collision detection and triggers collision events
     */
    void CheckCollisions();

    /**
     * @brief Gets the collection of all colliders in the scene
     * @return Const reference to the colliders vector
     */
    const std::vector<AABBColliderComponent*>& GetColliders() const { return mColliders; };

    /**
     * @brief Gets the collection of all active actors in the scene
     * @return Const reference to the actors vector
     */
    const std::vector<Actor*>& GetActors() const { return mActors; }

    /**
     * @brief Gets the renderer interface for this scene
     * @return Reference to the renderer implementation
     */
    IRenderer& GetRenderer();
};
