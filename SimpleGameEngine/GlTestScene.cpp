#include "GlTestScene.h"
#include "Assets.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "Camera.h"
#include "FPSController.h"
#include "MoveComponent.h"
#include "AABBColliderComponent.h"
#include <iostream>

Actor* actor;
Actor* cubeActor;
Actor* cubeActor2;

AABBColliderComponent* cubeCollider;
AABBColliderComponent* cubeCollider2;
AABBColliderComponent* cameraCollider;

Vector3 spritePosition{ 250, 250, 1000 };
Vector3 spriteRotation{ 0, 0, 0};
Vector3 spriteScale{ 0.2, 0.2, 0.2 };

Vector3 meshPosition{ 0, -10, 0 };
Vector3 meshRotation{ 0, 0, 0 };
Vector3 meshScale{ 10, 10, 10 };

Vector3 meshPosition2{ 0, -10, 0 };
Vector3 meshRotation2{ 90, 0, 0 };
Vector3 meshScale2{ 10, 10, 10 };

Camera* cam;

GlTestScene::GlTestScene()
{
}

void GlTestScene::Start()
{

}

void GlTestScene::Render()
{
}

void GlTestScene::Update()
{

	CheckCollisions();
}

void GlTestScene::Close()
{
}

void GlTestScene::Load()
{
	mSimpleFrag->Load("Sprite.frag", FRAGMENT);
	mSimpleVert->Load("Transform.vert", VERTEX);

	sp->Compose({ mSimpleFrag, mSimpleVert });

	mRenderer->SetSpriteShaderProgram(sp);

	actor = new Actor();
	AddActor(actor);
	actor->SetPosition(spritePosition);
	actor->SetRotation(spriteRotation);
	actor->SetScale(spriteScale);

	cubeActor = new Actor();
	AddActor(cubeActor);
	cubeActor->SetPosition(meshPosition);
	cubeActor->SetRotation(meshRotation);
	cubeActor->SetScale(meshScale);

	cubeActor2 = new Actor();
	AddActor(cubeActor2);
	cubeActor2->SetPosition(meshPosition2);
	cubeActor2->SetRotation(meshRotation2);
	cubeActor2->SetScale(meshScale2);

	cam = new Camera();
	AddActor(cam);
	FPSController* cc = new FPSController(cam);
	cc->OnStart();


	Assets::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
	Assets::LoadTexture(*mRenderer, "Resources/wall.png", "wall");

	Assets::LoadMesh("Resources/Meshes/cube.obj", "cube");

	SpriteComponent* sprite = new SpriteComponent(actor, Assets::GetTexture("ball"));
	MeshComponent* mesh = new MeshComponent(cubeActor);
	MeshComponent* mesh2 = new MeshComponent(cubeActor2);
	mesh->SetMesh(Assets::GetMesh("cube"));
	mesh2->SetMesh(Assets::GetMesh("cube"));

	MoveComponent* move = new MoveComponent(cubeActor);
	move->SetSpeed(Vector2(0.0f, 0.0f));


	// Cube Collider
	cubeCollider = new AABBColliderComponent(cubeActor);
	cubeCollider->SetDimensions(Vector3(20.0f, 20.0f, 20.0f));
	cubeCollider->SetOnCollisionEnter([](AABBColliderComponent* other) {
		/*Vector3 currentpos = cubeActor->GetTransform().GetPosition();
		cubeActor->SetPosition(currentpos + Vector3{ 1, 0, 0 });*/
		MoveComponent* mMoveComponent = cubeActor->GetComponentOfType<MoveComponent>();
		mMoveComponent->SetSpeed(Vector2(5.0f, 0.0f));
		});
	cubeCollider->SetOnCollisionExit([](AABBColliderComponent* other) {
		MoveComponent* mMoveComponent = cubeActor->GetComponentOfType<MoveComponent>();
		mMoveComponent->SetSpeed(Vector2(0.0f, 0.0f));
		});

	// Cube 2 Collider
	cubeCollider2 = new AABBColliderComponent(cubeActor2);
	cubeCollider2->SetDimensions(Vector3(20.0f, 20.0f, 20.0f));

	 // Cam collider
	//cameraCollider = new AABBColliderComponent(cam);
	//cameraCollider->SetDimensions(Vector3(10.0f, 10.0f, 10.0f));

}
