#include "GlTestScene.h"

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
	mSimpleFrag->Load("Simple.frag", FRAGMENT);
	mSimpleVert->Load("Simple.vert", VERTEX);

	sp->Compose({ mSimpleFrag, mSimpleVert });
}
