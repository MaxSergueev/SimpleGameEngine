#include "BowlingScene.h"
#include "Assets.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "Camera.h"
#include "FPSController.h"
#include "MoveComponent.h"
#include "AABBColliderComponent.h"
#include "Pin.h"
#include "BowlingBall.h"
#include "BowlingBallController.h"
#include <iostream>

Actor* bowlingSky;
Actor* bowlingFloor;
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
	Assets::LoadShaderProgram("Transform.vert", "Sprite.frag", "sp");
	Assets::LoadShaderProgram("Basic.vert", "BasicPin.frag", "pinSP");
	Assets::LoadShaderProgram("Basic.vert", "BasicFloor.frag", "floorSP");
	Assets::LoadShaderProgram("Basic.vert", "BasicBall.frag", "ballSP");
	mRenderer->SetSpriteShaderProgram(sp);


	camera = new Camera();
	AddActor(camera);
	FPSController* cc = new FPSController(camera);
	cc->OnStart();

	Assets::LoadTexture(*mRenderer, "Resources/wall.png", "wall");
	Assets::LoadTexture(*mRenderer, "Resources/floor.png", "floor");
	Assets::LoadTexture(*mRenderer, "Resources/pin.png", "pin");
	Assets::LoadTexture(*mRenderer, "Resources/bowlingball.png", "ball");
	Assets::LoadTexture(*mRenderer, "Resources/BowlingSky.png", "sky");

	Assets::LoadMesh("Resources/Meshes/sphere.obj", "sphere");
	Assets::LoadMesh("Resources/Meshes/sphere.obj", "skySphere");
	Assets::LoadMesh("Resources/Meshes/pin.obj", "pin");
	Assets::LoadMesh("Resources/Meshes/cube.obj", "cube");

	Pin* pin1 = new Pin(this, Vector3(0, -24, 200));

	Pin* pin2 = new Pin(this, Vector3(6, -24, 208));
	Pin* pin3 = new Pin(this, Vector3(-6, -24, 208));

	Pin* pin4 = new Pin(this, Vector3(0, -24, 216));
	Pin* pin5 = new Pin(this, Vector3(12, -24, 216));
	Pin* pin6 = new Pin(this, Vector3(-12, -24, 216));

	Pin* pin7 = new Pin(this, Vector3(6, -24, 224));
	Pin* pin8 = new Pin(this, Vector3(-6, -24, 224));
	Pin* pin9 = new Pin(this, Vector3(18, -24, 224));
	Pin* pin10 = new Pin(this, Vector3(-18, -24, 224));

	BowlingBall* ball = new BowlingBall(this, Vector3(0, -20, 0));
	ball->GetMeshComponent()->GetMesh()->SetShaderProgram(&Assets::GetShaderProgram("ballSP"));
	BowlingBallController* bc = new BowlingBallController(ball);
	bc->OnStart();


	bowlingSky = new Actor();
	AddActor(bowlingSky);
	bowlingSky->SetPosition(Vector3(0, 0, 0));
	bowlingSky->SetRotation(Vector3(180, 0, 180));
	bowlingSky->SetScale(Vector3(5000, 5000, 5000));
	MeshComponent* skymesh = new MeshComponent(bowlingSky);
	skymesh->SetMesh(Assets::GetMesh("skySphere"));
	skymesh->GetMesh()->SetTexture(&Assets::GetTexture("sky"));

	bowlingFloor = new Actor();
	AddActor(bowlingFloor);
	bowlingFloor->SetPosition(Vector3(0, -25, 0));
	bowlingFloor->SetRotation(Vector3(0, 0, 0));
	bowlingFloor->SetScale(Vector3(5000, 1, 5000));
	MeshComponent* floorMesh = new MeshComponent(bowlingFloor);
	floorMesh->SetMesh(Assets::GetMesh("cube"));
	floorMesh->GetMesh()->SetTexture(&Assets::GetTexture("floor"));
	floorMesh->GetMesh()->SetShaderProgram(&Assets::GetShaderProgram("floorSP"));

}