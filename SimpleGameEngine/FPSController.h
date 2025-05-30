#pragma once
#include "Component.h"
#include "IInputListener.h"
#include "Vector2.h"

class MoveComponent;
class FirstPersonActor;

class FPSController : public Component, public IInputListener
{
public:
    FPSController() = delete;
    FPSController(const FPSController&) = delete;
    FPSController& operator= (const FPSController&) = delete;

    FPSController(Actor* actor);
    ~FPSController();

    void OnStart() override;
    void Update() override;

    void OnNotify(SDL_Event& pEvent) override;

private:
    float mInputZ;
    float mInputX;
    MoveComponent* mMoveComponent;
    FirstPersonActor* mFirstPersonActor;
};


