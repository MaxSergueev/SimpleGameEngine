#include "BowlingBall.h"
#include "Assets.h"
#include "Scene.h"

BowlingBall::BowlingBall(Scene* scene, const Vector3& position) : mSpeed(30.0f), mMass(7.0f)
{
    scene->AddActor(this);

    SetPosition(position);
    SetRotation(Vector3(0, 0, 0));
    SetScale(Vector3(5.0f, 5.0f, 5.0f));

    mMeshComponent = new MeshComponent(this);
    mMeshComponent->SetMesh(Assets::GetMesh("sphere"));
    mMeshComponent->GetMesh()->SetTexture(&Assets::GetTexture("ball"));

    mMoveComponent = new MoveComponent(this);
    mMoveComponent->SetSpeed(Vector2(0.0f, 0.0f));

    mColliderComponent = new AABBColliderComponent(this);
    mColliderComponent->SetDimensions(Vector3(8.0f, 8.0f, 8.0f));
}

void BowlingBall::Roll(const Vector2& direction)
{
    Vector2 dirCopy = direction;

    // Normalize the direction and apply speed
    Vector2 normalizedDir = dirCopy;
    float sqrLength = dirCopy.GetSqrLength();
    if (sqrLength > 0.0f)
    {
        float length = sqrt(sqrLength);
        normalizedDir.x /= length;
        normalizedDir.y /= length;
    }

    mMoveComponent->SetSpeed(normalizedDir * mSpeed);
}


void BowlingBall::Stop()
{
    mMoveComponent->SetSpeed(Vector2(0.0f, 0.0f));
}
