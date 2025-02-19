#include "Pong.h"

#include <memory>

#include "../Assets.h"
#include "../SpriteComponent.h"

#include "../Time.h"

Pong::Pong():Scene("Pong")
{
    pos = {20, 20};
}

void Pong::Start()
{
}

void Pong::Render()
{
    pos = {pos.x + 5.0f * Time::deltaTime, pos.y};

    Rectangle r {{pos.x, pos.y}, {20, 20}};
    mRenderer->DrawRect(r);
}

void Pong::Update()
{
}

void Pong::OnInputs(SDL_Event pEvent)
{
}

void Pong::Close()
{
}

void Pong::Load()
{
    Assets::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
    Actor* actor = new Actor();
    SpriteComponent* sprite =  new SpriteComponent(actor, Assets::GetTexture("ball"));
    actor->SetPosition(Vector2{500, 500});
}