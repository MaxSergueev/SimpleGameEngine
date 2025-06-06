#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "AABBColliderComponent.h"

/**
 * @brief Physics-based bowling ball actor for bowling game mechanics
 *
 * BowlingBall represents a heavy spherical object that can be rolled in a specified
 * direction with realistic physics properties. It combines visual representation,
 * movement mechanics, and collision detection to simulate a bowling ball's behavior.
 * The ball can be controlled programmatically and includes mass properties for
 * potential physics interactions with other objects.
 */
class BowlingBall : public Actor
{
private:
    MeshComponent* mMeshComponent;          ///< Visual sphere representation of the ball
    MoveComponent* mMoveComponent;          ///< Handles directional movement
    AABBColliderComponent* mColliderComponent; ///< Collision detection for physics
    float mSpeed;                           ///< Rolling speed in units per second
    float mMass;                            ///< Mass of the ball for physics calculations

public:
    /**
     * @brief Constructs a bowling ball at the specified position
     * @param scene Pointer to the scene that will contain the bowling ball
     * @param position Starting world position (default: Vector3(0, 5, 0))
     */
    BowlingBall(Scene* scene, const Vector3& position = Vector3(0, 5, 0));

    /**
     * @brief Default destructor
     */
    ~BowlingBall() override = default;

    /**
     * @brief Gets the mesh component for visual representation
     * @return Pointer to the mesh component
     */
    MeshComponent* GetMeshComponent() const { return mMeshComponent; }

    /**
     * @brief Gets the movement component for physics control
     * @return Pointer to the movement component
     */
    MoveComponent* GetMoveComponent() const { return mMoveComponent; }

    /**
     * @brief Gets the collision component for physics interactions
     * @return Pointer to the AABB collider component
     */
    AABBColliderComponent* GetColliderComponent() const { return mColliderComponent; }

    /**
     * @brief Rolls the ball in the specified direction
     * @param direction 2D direction vector (will be normalized automatically)
     */
    void Roll(const Vector2& direction);

    /**
     * @brief Stops the ball's movement immediately
     */
    void Stop();

    /**
     * @brief Sets the rolling speed of the ball
     * @param speed New speed in units per second
     */
    void SetSpeed(float speed) { mSpeed = speed; }

    /**
     * @brief Gets the current rolling speed
     * @return Current speed in units per second
     */
    float GetSpeed() const { return mSpeed; }

    /**
     * @brief Gets the mass of the bowling ball
     * @return Mass value for physics calculations
     */
    float GetMass() const { return mMass; }
};




