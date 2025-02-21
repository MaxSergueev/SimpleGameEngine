#include "Pong.h"

#include <memory>

#include "../Assets.h"
#include "../SpriteComponent.h"

#include "../Time.h"

#include <vector>
#include "../AnimatedSpriteComponent.h"

Pong::Pong():Scene("Pong")
{
}

void Pong::Start()
{
}

void Pong::Render()
{
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
    std::vector<Texture*> WalkCycle{};
    for (int i = 0; i < 9; i++) {
        Assets::LoadTexture(*mRenderer, "Resources/WalkCycle/0" + std::to_string(i) + "_MouseWalk.png", "0" + std::to_string(i) + "MW");
        WalkCycle.push_back(&Assets::GetTexture("0" + std::to_string(i) + "MW"));

    }
    Actor* actor = new Actor();
    AddActor(actor);
    actor->SetPosition(Vector2{ 250, 250 });
    actor->SetScale(Vector2{ 1.0f, 1.0f });

    AnimatedSpriteComponent* anim = new AnimatedSpriteComponent(actor, WalkCycle);
    anim->SetAnimationFps(12);

    //PokeBall
    Assets::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
    //SpriteComponent* sprite =  new SpriteComponent(actor, Assets::GetTexture("ball"));
}