#include "Pong.h"

#include <memory>

#include "../Assets.h"
#include "../SpriteComponent.h"

#include "../Time.h"

#include <vector>
#include "../AnimatedSpriteComponent.h"
#include "../MoveComponent.h"

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
    actor->SetPosition(Vector2{ 400, 400 });

    AnimatedSpriteComponent* anim = new AnimatedSpriteComponent(actor, WalkCycle);
    MoveComponent* move = new MoveComponent(actor);
    anim->SetAnimationFps(12);
    move->SetSpeed(-15.0f);

    //PokeBall
    Assets::LoadTexture(*mRenderer, "Resources/pokeball.png", "ball");
    Actor* ballActor = new Actor();
    AddActor(ballActor);
    SpriteComponent* sprite =  new SpriteComponent(ballActor, Assets::GetTexture("ball"));
    ballActor->SetPosition(Vector2{ 865, 500 });
    ballActor->SetScale(Vector2{ 0.15f, 0.15f });
}