#include "Pin.h"
#include "Assets.h"
#include "Scene.h"

Pin::Pin(Scene* scene, const Vector3& position)
{
    // Add this actor to the scene
    scene->AddActor(this);

    // Set initial transform
    SetPosition(position);
    SetRotation(Vector3(0, 0, 0));
    SetScale(Vector3(2.5f, 2.5f, 2.5f));

    // Create and setup mesh component
    mMeshComponent = new MeshComponent(this);
    mMeshComponent->SetMesh(Assets::GetMesh("pin"));
    mMeshComponent->GetMesh()->SetTexture(&Assets::GetTexture("pin"));

    // Create and setup move component
    mMoveComponent = new MoveComponent(this);
    mMoveComponent->SetSpeed(Vector2(0.0f, 0.0f));

    // Create and setup collider component
    mColliderComponent = new AABBColliderComponent(this);
    mColliderComponent->SetDimensions(Vector3(7.5f, 10.0f, 7.5f));

    // Setup collision callbacks
    SetupCollisionCallbacks();
}

void Pin::SetupCollisionCallbacks()
{
    mColliderComponent->SetOnCollisionEnter([this](AABBColliderComponent* other) {
        mMoveComponent->SetSpeed(Vector2(5.0f, 0.0f));
        });

    mColliderComponent->SetOnCollisionExit([this](AABBColliderComponent* other) {
        mMoveComponent->SetSpeed(Vector2(0.0f, 0.0f));
        });
}
