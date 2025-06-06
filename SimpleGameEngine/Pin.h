#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "AABBColliderComponent.h"
#include "PinPhysicsComponent.h"

/**
 * @brief Bowling pin actor with physics interactions
 *
 * Pin represents a bowling pin that can be knocked down by bowling balls or other pins.
 * It features physics simulation including collision response, momentum transfer,
 * and chain reactions between pins. The pin tracks its knocked state and applies
 * appropriate forces when hit by balls or other moving pins, creating authentic
 * bowling gameplay mechanics.
 */
class Pin : public Actor
{
private:
    MeshComponent* mMeshComponent;          ///< Visual representation of the pin
    MoveComponent* mMoveComponent;          ///< Handles pin movement when knocked
    AABBColliderComponent* mColliderComponent; ///< Collision detection for physics
    PinPhysicsComponent* mPhysicsComponent; ///< Custom physics behavior for pins
    bool mIsKnocked;                        ///< Whether pin has been knocked down
    float mMass;                            ///< Mass for physics calculations

public:
    /**
     * @brief Constructs a bowling pin at the specified position
     * @param scene Pointer to the scene that will contain the pin
     * @param position Starting world position (default: Vector3(0, 0, 0))
     */
    Pin(Scene* scene, const Vector3& position = Vector3(0, 0, 0));

    /**
     * @brief Default destructor
     */
    ~Pin() override = default;

    /**
     * @brief Gets the mesh component for visual representation
     * @return Pointer to the mesh component
     */
    MeshComponent* GetMeshComponent() const { return mMeshComponent; }

    /**
     * @brief Gets the movement component for physics motion
     * @return Pointer to the movement component
     */
    MoveComponent* GetMoveComponent() const { return mMoveComponent; }

    /**
     * @brief Gets the collision component for physics interactions
     * @return Pointer to the AABB collider component
     */
    AABBColliderComponent* GetColliderComponent() const { return mColliderComponent; }

    /**
     * @brief Gets the specialized physics component for pin behavior
     * @return Pointer to the pin physics component
     */
    PinPhysicsComponent* GetPhysicsComponent() const { return mPhysicsComponent; }

    /**
     * @brief Sets up collision detection and response callbacks
     */
    void SetupCollisionCallbacks();

    /**
     * @brief Applies an impulse force to the pin in the specified direction
     * @param direction 2D direction vector for the force application
     * @param force Magnitude of the force to apply
     */
    void ApplyImpulse(const Vector2& direction, float force);

    /**
     * @brief Checks if the pin has been knocked down
     * @return True if pin is knocked, false if still standing
     */
    bool IsKnocked() const { return mIsKnocked; }

    /**
     * @brief Sets the knocked state of the pin
     * @param knocked New knocked state (true = knocked down, false = standing)
     */
    void SetKnocked(bool knocked) { mIsKnocked = knocked; }

    /**
     * @brief Gets the mass of the pin for physics calculations
     * @return Mass value used in collision response
     */
    float GetMass() const { return mMass; }
};
