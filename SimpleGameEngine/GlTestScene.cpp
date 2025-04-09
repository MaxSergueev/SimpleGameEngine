#include "GlTestScene.h"
#include "Assets.h"
#include "SpriteComponent.h"
#include "MeshComponent.h"
#include "Camera.h"
#include "FPSController.h"

Actor* actor;
Actor* cubeActor;
Actor* cube2Actor;

Vector3 spritePosition{ 250, 250, 1000 };
Vector3 spriteRotation{ 0, 0, 0};
Vector3 spriteScale{ 0.2, 0.2, 0.2 };

Vector3 meshPosition{ 0, -10, 0 };
Vector3 meshRotation{ 90, 0, 0 };
Vector3 meshScale{ 100, 100, 1 };

Vector3 mesh2Position{ 150, -10, 0 };
Vector3 mesh2Rotation{ 90, 0, 0 };
Vector3 mesh2Scale{ 100, 100, 1 };

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
	//cubeActor->Rotate(Vector3(1, 0, 0));
	//actor->RotateAroundAxis(rotation, 2);
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

	cube2Actor = new Actor();
	cube2Actor->SetPosition(mesh2Position);
	cube2Actor->SetRotation(mesh2Rotation);
	cube2Actor->SetScale(mesh2Scale);

	cam = new Camera();
	AddActor(cam);
	FPSController* cc = new FPSController(cam);
	cc->OnStart();


	Assets::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
	Assets::LoadTexture(*mRenderer, "Resources/wall.png", "wall");

	Assets::LoadShaderProgram("Basic.vert", "Basic.frag", "basic");

	SpriteComponent* sprite = new SpriteComponent(actor, Assets::GetTexture("ball"));
	MeshComponent* mesh = new MeshComponent(cubeActor);
	MeshComponent* mesh2 = new MeshComponent(cube2Actor);
	mesh2->GetMesh()->SetShaderProgram(&Assets::GetShaderProgram("basic"));

}
