#pragma once
#include "Component.h"
#include "Vector2.h"

/**
 * @brief Component that handles actor movement based on speed and direction
 *
 * MoveComponent provides basic movement functionality for actors by applying
 * velocity-based translation each frame. It uses the actor's transform to
 * determine movement directions (right and forward vectors) and applies
 * movement relative to the actor's current orientation.
 */
class MoveComponent : public Component
{
protected:
    Vector2 mSpeed;     ///< Movement speed in X (right) and Y (forward) directions

public:
    /**
     * @brief Constructs a movement component for the specified actor
     * @param pOwner The actor that owns this component
     * @param pUpdateOrder Component update priority (default: 100)
     */
    MoveComponent(Actor* pOwner, int pUpdateOrder = 100);

    MoveComponent() = delete;
    MoveComponent(const MoveComponent&) = delete;
    MoveComponent& operator= (const MoveComponent&) = delete;

    /**
     * @brief Gets the current movement speed vector
     * @return Current speed in X (right) and Y (forward) directions
     */
    Vector2 GetSpeed() const { return mSpeed; }

    /**
     * @brief Sets the movement speed vector
     * @param pSpeed New speed values for X (right) and Y (forward) movement
     */
    void SetSpeed(Vector2 pSpeed);

    /**
     * @brief Called when the component starts - currently unused
     */
    virtual void OnStart() override;

    /**
     * @brief Updates actor position based on current speed and delta time
     */
    void Update() override;
};
