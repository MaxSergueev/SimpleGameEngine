#include "GlTestScene.h"
#include "Assets.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "Camera.h"
#include "FPSController.h"

Actor* actor;
Actor* cubeActor;

Vector3 spritePosition{ 250, 250, 1000 };
Vector3 spriteRotation{ 0, 0, 0};
Vector3 spriteScale{ 0.2, 0.2, 0.2 };

Vector3 meshPosition{ 0, -10, 0 };
Vector3 meshRotation{ 90, 0, 0 };
Vector3 meshScale{ 10, 10, 10 };

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
	cubeActor->Rotate(Vector3(0.2, 0.1, 0.4));
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
	cubeActor->SetPosition(meshPosition);
	cubeActor->SetRotation(meshRotation);
	cubeActor->SetScale(meshScale);

	cam = new Camera();
	AddActor(cam);
	FPSController* cc = new FPSController(cam);
	cc->OnStart();


	Assets::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
	Assets::LoadTexture(*mRenderer, "Resources/wall.png", "wall");

	Assets::LoadMesh("Resources/Meshes/cube.obj", "cube");

	SpriteComponent* sprite = new SpriteComponent(actor, Assets::GetTexture("ball"));
	MeshComponent* mesh = new MeshComponent(cubeActor);
	mesh->SetMesh(Assets::GetMesh("cube"));

}
