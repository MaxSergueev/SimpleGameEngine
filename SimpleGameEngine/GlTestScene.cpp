#include "GlTestScene.h"
#include "Assets.h"
#include "SpriteComponent.h"

Actor* actor;
Vector3 rotation{ 0, 0, 0 };

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
	actor->SetPosition(Vector3{ 0, 0, 500 });
	actor->SetRotation(Vector3{ rotation });
	actor->SetScale(Vector3{ 0.2, 0.2, 0.2 });

	Assets::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
	SpriteComponent* sprite = new SpriteComponent(actor, Assets::GetTexture("ball"));

}
