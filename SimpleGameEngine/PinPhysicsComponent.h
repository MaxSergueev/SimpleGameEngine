#pragma once
#include "Component.h"
#include "MoveComponent.h"

/**
 * @brief Specialized physics component for bowling pin behavior
 *
 * PinPhysicsComponent provides friction and momentum simulation for
 * bowling pins. It applies dynamic friction based on movement speed to create
 * pin physics where pins gradually slow down after being knocked.
 * The component features speed-dependent friction coefficients and automatic
 * stopping for very slow movements to prevent infinite sliding.
 */
class PinPhysicsComponent : public Component
{
private:
    MoveComponent* mMoveComponent;  ///< Reference to the pin's movement component
    float mFrictionFactor;          ///< Base friction coefficient (0.0-1.0)

public:
    /**
     * @brief Constructs physics component for the specified actor
     * @param owner Pointer to the actor (typically a Pin) that owns this component
     */
    PinPhysicsComponent(class Actor* owner);

    /**
     * @brief Default destructor
     */
    ~PinPhysicsComponent() = default;

    /**
     * @brief Updates physics simulation each frame
     *
     * Applies dynamic friction based on current movement speed and stops
     * the pin when velocity becomes negligible to prevent infinite sliding.
     */
    void Update() override;

    /**
     * @brief Sets the base friction coefficient
     * @param factor Friction factor between 0.0 (no friction) and 1.0 (maximum friction)
     */
    void SetFrictionFactor(float factor) { mFrictionFactor = factor; }

    /**
     * @brief Gets the current friction coefficient
     * @return Current friction factor value
     */
    float GetFrictionFactor() const { return mFrictionFactor; }
};
