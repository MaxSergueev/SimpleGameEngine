#include "DoomScene.h"
#include "Assets.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "Camera.h"
#include "FPSController.h"
#include "MoveComponent.h"
#include "AABBColliderComponent.h"
#include "WallBlock.h"
#include <iostream>
#include "FirstPersonActor.h"
#include "Enemy.h"
#include "Time.h"
#include "BulletPool.h"

Actor* doomSky;
Actor* doomFloor;
FirstPersonActor* doomGuy;
Enemy* enemy1;
Enemy* enemy2;



DoomScene::DoomScene()
{
}

void DoomScene::Start()
{

}

void DoomScene::Render()
{
}

void DoomScene::Update()
{
	UpdateAllActors();
	CheckCollisions();
	//doomGuy->TakeDamage(1);
	//enemy1->TakeDamage(1);
}

void DoomScene::Close()
{
}

void DoomScene::Load()
{
	mSimpleFrag->Load("Sprite.frag", FRAGMENT);
	mSimpleVert->Load("Transform.vert", VERTEX);

	sp->Compose({ mSimpleFrag, mSimpleVert });

	Assets::LoadShaderProgram("Basic.vert", "BasicWall.frag", "wallSP");
	Assets::LoadShaderProgram("Basic.vert", "BasicFloor.frag", "floorSP");
	Assets::LoadShaderProgram("Basic.vert", "BasicBall.frag", "ballSP");
	mRenderer->SetSpriteShaderProgram(sp);

	Assets::LoadTexture(*mRenderer, "Resources/green.png", "doomWall");
	Assets::LoadTexture(*mRenderer, "Resources/floor.png", "floor");
	Assets::LoadTexture(*mRenderer, "Resources/BowlingSky.png", "sky");

	Assets::LoadTexture(*mRenderer, "Resources/bowlingball.png", "yellow");
	Assets::LoadTexture(*mRenderer, "Resources/purple.png", "purple");

	Assets::LoadMesh("Resources/Meshes/sphere.obj", "sphere");
	Assets::LoadMesh("Resources/Meshes/sphere.obj", "skySphere");
	Assets::LoadMesh("Resources/Meshes/sphere.obj", "enemy");
	Assets::LoadMesh("Resources/Meshes/sphere.obj", "bullet");
	Assets::LoadMesh("Resources/Meshes/cube.obj", "floorCube");
	Assets::LoadMesh("Resources/Meshes/cube.obj", "wallCube");

	mBulletPool = new BulletPool(this, 100);

	doomSky = new Actor();
	AddActor(doomSky);
	doomSky->SetPosition(Vector3(0, 0, 0));
	doomSky->SetRotation(Vector3(180, 0, 180));
	doomSky->SetScale(Vector3(5000, 5000, 5000));
	MeshComponent* skymesh = new MeshComponent(doomSky);
	skymesh->SetMesh(Assets::GetMesh("skySphere"));
	skymesh->GetMesh()->SetTexture(&Assets::GetTexture("sky"));

	doomFloor = new Actor();
	AddActor(doomFloor);
	doomFloor->SetPosition(Vector3(0, -45, 0));
	doomFloor->SetRotation(Vector3(0, 0, 0));
	doomFloor->SetScale(Vector3(5000, 1, 5000));
	MeshComponent* floorMesh = new MeshComponent(doomFloor);
	floorMesh->SetMesh(Assets::GetMesh("floorCube"));
	floorMesh->GetMesh()->SetTexture(&Assets::GetTexture("floor"));
	floorMesh->GetMesh()->SetShaderProgram(&Assets::GetShaderProgram("floorSP"));

	WallBlock* wall1 = new WallBlock(this, Vector3(0, 0, 300));
	WallBlock* wall2 = new WallBlock(this, Vector3(90, 0, 300));
	WallBlock* wall3 = new WallBlock(this, Vector3(180, 0, 300));
	WallBlock* wall4 = new WallBlock(this, Vector3(270, 0, 300));
	WallBlock* wall5 = new WallBlock(this, Vector3(-90, 0, 300));
	WallBlock* wall6 = new WallBlock(this, Vector3(-180, 0, 300));
	WallBlock* wall7 = new WallBlock(this, Vector3(-270, 0, 300));
	WallBlock* wall8 = new WallBlock(this, Vector3(-360, 0, 300));

	//WallBlock* wall9 = new WallBlock(this, Vector3(0, 0, -240));
	WallBlock* wall10 = new WallBlock(this, Vector3(90, 0, -240));
	WallBlock* wall11 = new WallBlock(this, Vector3(180, 0, -240));
	WallBlock* wall12 = new WallBlock(this, Vector3(270, 0, -240));
	WallBlock* wall13 = new WallBlock(this, Vector3(-90, 0, -240));
	//WallBlock* wall14 = new WallBlock(this, Vector3(-180, 0, -240));
	WallBlock* wall15 = new WallBlock(this, Vector3(-270, 0, -240));
	WallBlock* wall16 = new WallBlock(this, Vector3(-360, 0, -240));

	WallBlock* wall17 = new WallBlock(this, Vector3(-360, 0, 210));
	WallBlock* wall18 = new WallBlock(this, Vector3(-360, 0, 120));
	WallBlock* wall19 = new WallBlock(this, Vector3(-360, 0, 30));
	WallBlock* wall20 = new WallBlock(this, Vector3(-360, 0, -60));
	WallBlock* wall21 = new WallBlock(this, Vector3(-360, 0, -150));

	WallBlock* wall22 = new WallBlock(this, Vector3(270, 0, 210));
	WallBlock* wall23 = new WallBlock(this, Vector3(270, 0, 120));
	WallBlock* wall24 = new WallBlock(this, Vector3(270, 0, 30));
	WallBlock* wall25 = new WallBlock(this, Vector3(270, 0, -60));
	WallBlock* wall26 = new WallBlock(this, Vector3(270, 0, -150));

	 doomGuy = new FirstPersonActor(this, mBulletPool);

	 // Create some enemies
	 enemy1 = new Enemy(this, Vector3(-100, 0, 100), mBulletPool);
	 enemy2 = new Enemy(this, Vector3(100, 0, 200), mBulletPool);
	 enemy2->SetPatrolDirection(Vector3(-1, 0, 0));
	



}

DoomScene::~DoomScene()
{
	delete mBulletPool;
}
