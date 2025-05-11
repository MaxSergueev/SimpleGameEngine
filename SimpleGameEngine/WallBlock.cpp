#include "Assets.h"
#include "Scene.h"
#include "BowlingBall.h"
#include <cmath>
#include "WallBlock.h"

WallBlock::WallBlock(Scene* scene, const Vector3& position)
{
    scene->AddActor(this);

    SetPosition(position);
    SetRotation(Vector3(0, 0, 0));
    SetScale(Vector3(45.0f, 45.0f, 45.0f));

    mMeshComponent = new MeshComponent(this);
    mMeshComponent->SetMesh(Assets::GetMesh("wallCube"));
    mMeshComponent->GetMesh()->SetTexture(&Assets::GetTexture("doomWall"));
    mMeshComponent->GetMesh()->SetShaderProgram(&Assets::GetShaderProgram("wallSP"));

    mColliderComponent = new AABBColliderComponent(this);
    mColliderComponent->SetDimensions(Vector3(20.0f, 20.0f, 20.0f));
}
