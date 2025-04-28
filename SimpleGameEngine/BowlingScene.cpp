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

Actor* skyBox;
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

	camera = new Camera();
	AddActor(camera);
	FPSController* cc = new FPSController(camera);
	cc->OnStart();

	Assets::LoadTexture(*mRenderer, "Resources/wall.png", "wall");
	Assets::LoadTexture(*mRenderer, "Resources/pin.jpg", "pin");
	Assets::LoadTexture(*mRenderer, "Resources/ball.jpg", "ball");
	Assets::LoadTexture(*mRenderer, "Resources/Sky2.png", "sky");

	Assets::LoadMesh("Resources/Meshes/sphere.obj", "sphere");
	Assets::LoadMesh("Resources/Meshes/pin.obj", "pin");

	Pin* pin1 = new Pin(this, Vector3(0, 0, 200));

	Pin* pin2 = new Pin(this, Vector3(6, 0, 208));
	Pin* pin3 = new Pin(this, Vector3(-6, 0, 208));

	Pin* pin4 = new Pin(this, Vector3(0, 0, 216));
	Pin* pin5 = new Pin(this, Vector3(12, 0, 216));
	Pin* pin6 = new Pin(this, Vector3(-12, 0, 216));

	Pin* pin7 = new Pin(this, Vector3(6, 0, 224));
	Pin* pin8 = new Pin(this, Vector3(-6, 0, 224));
	Pin* pin9 = new Pin(this, Vector3(18, 0, 224));
	Pin* pin10 = new Pin(this, Vector3(-18, 0, 224));

	BowlingBall* ball = new BowlingBall(this, Vector3(0, 0, 0));
	BowlingBallController* bc = new BowlingBallController(ball);
	bc->OnStart();

}