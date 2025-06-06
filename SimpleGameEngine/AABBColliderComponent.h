#pragma once
#include "Component.h"
#include "Vector3.h"
#include <functional>
#include <vector>

/**
 * @brief Axis-Aligned Bounding Box collision component for 3D collision detection
 *
 * This component provides AABB collision detection capabilities to actors.
 * It supports both solid colliders and triggers, with callback functions
 * for collision events (enter, stay, exit).
 */
class AABBColliderComponent : public Component
{
private:
    Vector3 mMin;           ///< World space minimum bounds
    Vector3 mMax;           ///< World space maximum bounds
    Vector3 mOffset;        ///< Local offset from actor position
    Vector3 mDimensions;    ///< Local space dimensions of the collider
    bool mIsTrigger;        ///< Whether this collider is a trigger (no physical collision)
    bool mIsActive;         ///< Whether collision detection is active

    /// Callback invoked when collision starts
    std::function<void(AABBColliderComponent*)> mOnCollisionEnter;
    /// Callback invoked while collision continues
    std::function<void(AABBColliderComponent*)> mOnCollisionStay;
    /// Callback invoked when collision ends
    std::function<void(AABBColliderComponent*)> mOnCollisionExit;

    /// List of currently colliding components
    std::vector<AABBColliderComponent*> mCurrentCollisions;

public:
    /**
     * @brief Constructs an AABB collider component
     * @param pOwner The actor that owns this component
     */
    AABBColliderComponent(class Actor* pOwner);

    /**
     * @brief Destructor - unregisters from collision system
     */
    virtual ~AABBColliderComponent();

    /**
     * @brief Updates world space bounds based on actor transform
     */
    void UpdateWorldBounds();

    /**
     * @brief Sets the local dimensions of the collider
     * @param dimensions The new dimensions in local space
     */
    void SetDimensions(const Vector3& dimensions);

    /**
     * @brief Sets the local offset from the actor's position
     * @param offset The offset in local space
     */
    void SetOffset(const Vector3& offset);

    /**
     * @brief Sets whether this collider is a trigger
     * @param isTrigger True for trigger, false for solid collider
     */
    void SetTrigger(bool isTrigger) { mIsTrigger = isTrigger; }

    /**
     * @brief Sets whether collision detection is active
     * @param isActive True to enable collision detection
     */
    void SetActive(bool isActive) { mIsActive = isActive; }

    /**
     * @brief Gets the world space minimum bounds
     * @return Reference to minimum bounds vector
     */
    const Vector3& GetMin() const { return mMin; }

    /**
     * @brief Gets the world space maximum bounds
     * @return Reference to maximum bounds vector
     */
    const Vector3& GetMax() const { return mMax; }

    /**
     * @brief Tests intersection with another AABB collider
     * @param other The other collider to test against
     * @return True if the colliders intersect
     */
    bool Intersects(const AABBColliderComponent* other) const;

    /**
     * @brief Sets callback for collision enter events
     * @param callback Function to call when collision begins
     */
    void SetOnCollisionEnter(std::function<void(AABBColliderComponent*)> callback) { mOnCollisionEnter = callback; }

    /**
     * @brief Sets callback for collision stay events
     * @param callback Function to call while collision continues
     */
    void SetOnCollisionStay(std::function<void(AABBColliderComponent*)> callback) { mOnCollisionStay = callback; }

    /**
     * @brief Sets callback for collision exit events
     * @param callback Function to call when collision ends
     */
    void SetOnCollisionExit(std::function<void(AABBColliderComponent*)> callback) { mOnCollisionExit = callback; }

    /**
     * @brief Handles collision enter event
     * @param other The collider that entered collision
     */
    void OnCollisionEnter(AABBColliderComponent* other);

    /**
     * @brief Handles collision stay event
     * @param other The collider that is still colliding
     */
    void OnCollisionStay(AABBColliderComponent* other);

    /**
     * @brief Handles collision exit event
     * @param other The collider that exited collision
     */
    void OnCollisionExit(AABBColliderComponent* other);

    /**
     * @brief Updates the component each frame
     */
    void Update() override;

    /**
     * @brief Checks if currently colliding with specific collider
     * @param other The collider to check
     * @return True if currently colliding with the specified collider
     */
    bool IsCollidingWith(AABBColliderComponent* other) const;

    /**
     * @brief Gets list of all currently colliding components
     * @return Reference to vector of colliding components
     */
    const std::vector<AABBColliderComponent*>& GetCurrentCollisions() const { return mCurrentCollisions; }

    /**
     * @brief Gets whether this collider is a trigger
     * @return True if this is a trigger collider
     */
    bool IsTrigger() const { return mIsTrigger; }

    /**
     * @brief Gets whether collision detection is active
     * @return True if collision detection is active
     */
    bool IsActive() const { return mIsActive; }

    /**
     * @brief Gets the owning actor
     * @return Pointer to the actor that owns this component
     */
    class Actor* GetOwner() const { return mOwner; }
};

