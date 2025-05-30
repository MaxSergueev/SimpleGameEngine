#include "LineTrace.h"
#include "Scene.h"
#include "AABBColliderComponent.h"
#include <algorithm>
#include <limits>

LineTraceHit LineTrace::TraceLineAgainstColliders(Scene* scene, const Vector3& start, const Vector3& end, AABBColliderComponent* ignoreCollider)
{
    LineTraceHit result;
    float closestDistance = std::numeric_limits<float>::max();

    const auto& colliders = scene->GetColliders();

    for (AABBColliderComponent* collider : colliders)
    {
        if (!collider->IsActive() || collider == ignoreCollider)
            continue;

        Vector3 hitPoint;
        float distance;

        if (LineIntersectsAABB(start, end, collider->GetMin(), collider->GetMax(), hitPoint, distance))
        {
            if (distance < closestDistance)
            {
                closestDistance = distance;
                result.bHit = true;
                result.hitLocation = hitPoint;
                result.hitCollider = collider;
                result.distance = distance;
            }
        }
    }

    return result;
}

bool LineTrace::HasLineOfSight(Scene* scene, const Vector3& start, const Vector3& end, AABBColliderComponent* ignoreCollider)
{
    LineTraceHit hit = TraceLineAgainstColliders(scene, start, end, ignoreCollider);
    return !hit.bHit;
}

// Add this new function to LineTrace.cpp
bool LineTrace::HasLineOfSightToTarget(Scene* scene, const Vector3& start, const Vector3& end,
    AABBColliderComponent* shooterCollider,
    AABBColliderComponent* targetCollider)
{
    LineTraceHit hit = TraceLineAgainstColliders(scene, start, end, shooterCollider);

    if (!hit.bHit) {
        // Nothing hit - clear line of sight
        return true;
    }

    // Something was hit - check if it's our target
    if (hit.hitCollider == targetCollider) {
        // We hit our target - that's a clear line of sight for shooting purposes
        return true;
    }

    // We hit something else (wall, other enemy, etc.) - line of sight blocked
    return false;
}

bool LineTrace::LineIntersectsAABB(const Vector3& lineStart, const Vector3& lineEnd, const Vector3& aabbMin, const Vector3& aabbMax, Vector3& hitPoint, float& distance)
{
    Vector3 direction = lineEnd - lineStart;
    float lineLength = direction.Length();

    if (lineLength == 0.0f)
        return false;

    // Normalize
    direction.x = direction.x / lineLength;
	direction.y = direction.y / lineLength;
	direction.z = direction.z / lineLength;

    // Calculate intersection using slab method
    float tMin = 0.0f;
    float tMax = lineLength;

    for (int i = 0; i < 3; i++) // x, y, z components
    {
        float dirComponent = (i == 0) ? direction.x : (i == 1) ? direction.y : direction.z;
        float startComponent = (i == 0) ? lineStart.x : (i == 1) ? lineStart.y : lineStart.z;
        float minComponent = (i == 0) ? aabbMin.x : (i == 1) ? aabbMin.y : aabbMin.z;
        float maxComponent = (i == 0) ? aabbMax.x : (i == 1) ? aabbMax.y : aabbMax.z;

        if (abs(dirComponent) < 0.0001f) // Ray is parallel to slab
        {
            if (startComponent < minComponent || startComponent > maxComponent)
                return false;
        }
        else
        {
            float t1 = (minComponent - startComponent) / dirComponent;
            float t2 = (maxComponent - startComponent) / dirComponent;

            if (t1 > t2)
                std::swap(t1, t2);

            tMin = std::max(tMin, t1);
            tMax = std::min(tMax, t2);

            if (tMin > tMax)
                return false;
        }
    }

    if (tMin >= 0.0f && tMin <= lineLength)
    {
        hitPoint = lineStart + direction * tMin;
        distance = tMin;
        return true;
    }

    return false;
}
