#include "GlTestScene.h"
#include "Assets.h"
#include "SpriteComponent.h"

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

	Actor* actor = new Actor();
	AddActor(actor);
	actor->SetPosition(Vector3{ 400, 400, 0});

	Assets::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
	SpriteComponent* sprite = new SpriteComponent(actor, Assets::GetTexture("ball"));

}
