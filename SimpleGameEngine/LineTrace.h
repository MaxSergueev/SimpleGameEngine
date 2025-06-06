#pragma once
#include "Vector3.h"
#include <vector>

class AABBColliderComponent;
class Scene;

/**
 * @brief Result structure for line trace operations
 *
 * LineTraceHit contains information about a line trace collision,
 * including whether a hit occurred, the hit location, the collider
 * that was hit, and the distance to the hit point.
 */
struct LineTraceHit
{
    bool bHit;                          ///< Whether the line trace hit something
    Vector3 hitLocation;                ///< World position where the hit occurred
    AABBColliderComponent* hitCollider; ///< The collider component that was hit
    float distance;                     ///< Distance from start point to hit location

    /**
     * @brief Default constructor - initializes to no hit
     */
    LineTraceHit() : bHit(false), hitCollider(nullptr), distance(0.0f) {}
};

/**
 * @brief Static utility class for performing line trace collision detection
 *
 * LineTrace provides functionality for casting rays through 3D space to detect
 * collisions with AABB colliders. It supports line-of-sight checks, obstacle
 * detection, and target-specific visibility testing for AI and gameplay systems.
 */
class LineTrace
{
public:
    /**
     * @brief Performs a line trace against all colliders in a scene
     * @param scene The scene containing colliders to test against
     * @param start Starting point of the line trace
     * @param end Ending point of the line trace
     * @param ignoreCollider Optional collider to ignore during the trace
     * @return LineTraceHit structure containing hit information
     */
    static LineTraceHit TraceLineAgainstColliders(
        Scene* scene,
        const Vector3& start,
        const Vector3& end,
        AABBColliderComponent* ignoreCollider = nullptr
    );

    /**
     * @brief Checks if there's an unobstructed line of sight between two points
     * @param scene The scene containing colliders to test against
     * @param start Starting point of the line of sight check
     * @param end Ending point of the line of sight check
     * @param ignoreCollider Optional collider to ignore during the check
     * @return True if there are no obstructions between the points
     */
    static bool HasLineOfSight(
        Scene* scene,
        const Vector3& start,
        const Vector3& end,
        AABBColliderComponent* ignoreCollider = nullptr
    );

    /**
     * @brief Checks if there's line of sight to a specific target
     * @param scene The scene containing colliders to test against
     * @param start Starting point of the line of sight check
     * @param end Ending point of the line of sight check
     * @param shooterCollider The collider of the entity performing the check
     * @param targetCollider The collider of the target entity
     * @return True if the target is visible (no obstructions or target is hit directly)
     */
    static bool HasLineOfSightToTarget(
        Scene* scene,
        const Vector3& start,
        const Vector3& end,
        AABBColliderComponent* shooterCollider,
        AABBColliderComponent* targetCollider
    );

private:
    /**
     * @brief Tests if a line segment intersects with an AABB
     * @param lineStart Starting point of the line segment
     * @param lineEnd Ending point of the line segment
     * @param aabbMin Minimum corner of the AABB
     * @param aabbMax Maximum corner of the AABB
     * @param hitPoint Output parameter for the intersection point
     * @param distance Output parameter for the distance to intersection
     * @return True if the line intersects the AABB
     */
    static bool LineIntersectsAABB(
        const Vector3& lineStart,
        const Vector3& lineEnd,
        const Vector3& aabbMin,
        const Vector3& aabbMax,
        Vector3& hitPoint,
        float& distance
    );
};