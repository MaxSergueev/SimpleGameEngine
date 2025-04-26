#include "BowlingScene.h"
#include "Assets.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "Camera.h"
#include "FPSController.h"
#include "MoveComponent.h"
#include "AABBColliderComponent.h"
#include <iostream>

Actor* pinActor;
Actor* ballActor;

AABBColliderComponent* PinCollider;
AABBColliderComponent* BallCollider;
AABBColliderComponent* characterCollider;

// pin
Vector3 MP{ 0, 0, 0 };
Vector3 MR{ 0, 0, 0 };
Vector3 MS{ 2.5f, 2.5f, 2.5f };

// ball
Vector3 MP2{ 0, 5, 0 };
Vector3 MR2{ 90, 0, 0 };
Vector3 MS2{ 5, 5, 5 };

Camera* camera;

BowlingScene::BowlingScene()
{
}

void BowlingScene::Start()
{

}

void BowlingScene::Render()
{
}

void BowlingScene::Update()
{

	CheckCollisions();
}

void BowlingScene::Close()
{
}

void BowlingScene::Load()
{
	mSimpleFrag->Load("Sprite.frag", FRAGMENT);
	mSimpleVert->Load("Transform.vert", VERTEX);

	sp->Compose({ mSimpleFrag, mSimpleVert });

	mRenderer->SetSpriteShaderProgram(sp);

	pinActor = new Actor();
	AddActor(pinActor);
	pinActor->SetPosition(MP);
	pinActor->SetRotation(MR);
	pinActor->SetScale(MS);

	ballActor = new Actor();
	AddActor(ballActor);
	ballActor->SetPosition(MP2);
	ballActor->SetRotation(MR2);
	ballActor->SetScale(MS2);

	camera = new Camera();
	AddActor(camera);
	FPSController* cc = new FPSController(camera);
	cc->OnStart();

	Assets::LoadTexture(*mRenderer, "Resources/wall.png", "wall");
	Assets::LoadTexture(*mRenderer, "Resources/pin.jpg", "pin");
	Assets::LoadTexture(*mRenderer, "Resources/ball.jpg", "ball");

	Assets::LoadMesh("Resources/Meshes/sphere.obj", "sphere");
	Assets::LoadMesh("Resources/Meshes/pin.obj", "pin");

	MeshComponent* mesh = new MeshComponent(pinActor);
	MeshComponent* mesh2 = new MeshComponent(ballActor);

	mesh->SetMesh(Assets::GetMesh("pin"));
	mesh->GetMesh()->SetTexture(&Assets::GetTexture("pin"));

	mesh2->SetMesh(Assets::GetMesh("sphere"));
	mesh2->GetMesh()->SetTexture(&Assets::GetTexture("ball"));

	MoveComponent* move = new MoveComponent(pinActor);
	move->SetSpeed(Vector2(0.0f, 0.0f));


	// Cube Collider
	PinCollider = new AABBColliderComponent(pinActor);
	PinCollider->SetDimensions(Vector3(10.0f, 10.0f, 10.0f));
	PinCollider->SetOnCollisionEnter([](AABBColliderComponent* other) {
		MoveComponent* mMoveComponent = pinActor->GetComponentOfType<MoveComponent>();
		mMoveComponent->SetSpeed(Vector2(5.0f, 0.0f));
		});
	PinCollider->SetOnCollisionExit([](AABBColliderComponent* other) {
		MoveComponent* mMoveComponent = pinActor->GetComponentOfType<MoveComponent>();
		mMoveComponent->SetSpeed(Vector2(0.0f, 0.0f));
		});

	// Cube 2 Collider
	BallCollider = new AABBColliderComponent(ballActor);
	BallCollider->SetDimensions(Vector3(8.0f, 8.0f, 8.0f));

}