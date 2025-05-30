#pragma once
#include "Vector3.h"
#include <vector>

class AABBColliderComponent;
class Scene;

struct LineTraceHit
{
    bool bHit;
    Vector3 hitLocation;
    AABBColliderComponent* hitCollider;
    float distance;

    LineTraceHit() : bHit(false), hitCollider(nullptr), distance(0.0f) {}
};

class LineTrace
{
public:
    // Perform a line trace from start to end
    static LineTraceHit TraceLineAgainstColliders(
        Scene* scene,
        const Vector3& start,
        const Vector3& end,
        AABBColliderComponent* ignoreCollider = nullptr
    );

    // Check if there's a clear line of sight between two points
    static bool HasLineOfSight(
        Scene* scene,
        const Vector3& start,
        const Vector3& end,
        AABBColliderComponent* ignoreCollider = nullptr
    );
    static bool HasLineOfSightToTarget(
    Scene* scene,
    const Vector3& start,
    const Vector3& end,
    AABBColliderComponent* shooterCollider,
    AABBColliderComponent* targetCollider
    );

private:
    // Check if a line intersects with an AABB
    static bool LineIntersectsAABB(
        const Vector3& lineStart,
        const Vector3& lineEnd,
        const Vector3& aabbMin,
        const Vector3& aabbMax,
        Vector3& hitPoint,
        float& distance
    );
};


