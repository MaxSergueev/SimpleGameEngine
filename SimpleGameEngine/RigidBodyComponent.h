#pragma once
#include "Component.h"
#include "Vector3.h"

class AABBColliderComponent;

/**
 * @brief Component that provides physics simulation for actors
 *
 * RigidBodyComponent implements basic physics behavior including velocity,
 * acceleration, mass, and gravity. It handles collision response by calculating
 * penetration vectors and reflecting velocity along collision normals.
 * Automatically creates an AABB collider if none exists on the actor.
 */
class RigidBodyComponent : public Component
{
public:
    /**
     * @brief Constructs a rigid body component for the specified actor
     * @param owner The actor that will have physics simulation applied
     */
    RigidBodyComponent(Actor* owner);

    /**
     * @brief Default destructor
     */
    ~RigidBodyComponent() override = default;

    /**
     * @brief Updates physics simulation each frame
     */
    void Update() override;

    /**
     * @brief Sets the current velocity vector
     * @param velocity The new velocity in world units per second
     */
    void SetVelocity(const Vector3& velocity) { mVelocity = velocity; }

    /**
     * @brief Gets the current velocity vector
     * @return Current velocity in world units per second
     */
    Vector3 GetVelocity() const { return mVelocity; }

    /**
     * @brief Sets the mass of the rigid body
     * @param mass The mass value (affects force response)
     */
    void SetMass(float mass) { mMass = mass; }

    /**
     * @brief Gets the current mass value
     * @return The mass of the rigid body
     */
    float GetMass() const { return mMass; }

    /**
     * @brief Enables or disables gravity application
     * @param useGravity True to apply gravity, false to disable
     */
    void SetGravity(bool useGravity) { mUseGravity = useGravity; }

    /**
     * @brief Checks if gravity is currently applied
     * @return True if gravity affects this rigid body
     */
    bool UsesGravity() const { return mUseGravity; }

    /**
     * @brief Applies a force to the rigid body
     * @param force The force vector to apply (converted to acceleration using F=ma)
     */
    void AddForce(const Vector3& force);

    /**
     * @brief Resolves collision with another collider
     * @param other The collider that this rigid body collided with
     */
    void ResolveCollision(AABBColliderComponent* other);

private:
    Vector3 mVelocity;      ///< Current velocity vector
    Vector3 mAcceleration;  ///< Current acceleration vector
    float mMass;            ///< Mass of the rigid body
    bool mUseGravity;       ///< Whether gravity affects this body
    AABBColliderComponent* mCollider; ///< Associated collider component

    /**
     * @brief Calculates penetration vector for collision resolution
     * @param other The collider to calculate penetration against
     * @return Vector representing how much to move to resolve collision
     */
    Vector3 CalculatePenetration(AABBColliderComponent* other);

    /**
     * @brief Calculates collision normal for velocity reflection
     * @param other The collider to calculate normal against
     * @return Normalized vector pointing away from the collision surface
     */
    Vector3 CalculateCollisionNormal(AABBColliderComponent* other);
};
