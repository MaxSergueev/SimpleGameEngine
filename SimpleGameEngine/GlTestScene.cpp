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
	mRenderer->Draw();
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
	mSimpleVert->Load("Sprite.vert", VERTEX);

	sp->Compose({ mSimpleFrag, mSimpleVert }); 

	Actor* actor = new Actor();
	AddActor(actor);
	actor->SetPosition(Vector2{ 400, 400 });

	Assets::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
	SpriteComponent* sprite = new SpriteComponent(actor, Assets::GetTexture("ball"));

}
