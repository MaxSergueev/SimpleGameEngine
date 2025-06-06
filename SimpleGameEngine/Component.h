#pragma once

class Actor;

/**
 * @brief Base class for all actor components in the engine
 *
 * Component provides the foundation for the component system, allowing
 * functionality to be attached to actors. Components have lifecycle methods
 * and an update order system for deterministic execution.
 */
class Component
{
protected:
    bool mIsActive;         ///< Whether this component is currently active
    Actor* mOwner;          ///< The actor that owns this component
    int mUpdateOrder;       ///< Update order priority (lower values update first)

public:
    Component() = delete;

    /**
     * @brief Constructs a component and attaches it to an actor
     * @param pOwner The actor that will own this component
     * @param pUpdateOrder Update priority (lower values update first, default 100)
     */
    Component(Actor* pOwner, int pUpdateOrder = 100);

    /**
     * @brief Virtual destructor - removes component from owner
     */
    virtual ~Component();

    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;

    /**
     * @brief Called when the component is first created - override for initialization
     */
    virtual void OnStart();

    /**
     * @brief Called every frame - override for component-specific update logic
     */
    virtual void Update();

    /**
     * @brief Called when the component is destroyed - override for cleanup
     */
    virtual void OnEnd();

    /**
     * @brief Gets the component's update order priority
     * @return The update order value
     */
    int GetUpdateOrder() { return mUpdateOrder; }
};

