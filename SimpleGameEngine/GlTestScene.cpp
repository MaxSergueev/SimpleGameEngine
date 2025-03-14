#include "GlTestScene.h"
#include "Assets.h"
#include "SpriteComponent.h"

Actor* actor;
Vector3 initialPosition{ 0, 0, 1000 };
Vector3 initialRotation{ 0, 0, 0};
Vector3 initialScale{ 0.2, 0.2, 0.2 };

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
	actor->Rotate(Vector3(1, 0, 1));
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

	mRenderer->SetShaderProgram(sp);

	actor = new Actor();
	AddActor(actor);
	actor->SetPosition(initialPosition);
	actor->SetRotation(initialRotation);
	actor->SetScale(initialScale);

	Assets::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
	SpriteComponent* sprite = new SpriteComponent(actor, Assets::GetTexture("ball"));

}
