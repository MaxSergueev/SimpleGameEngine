#pragma once
#include "Component.h"
#include "IInputListener.h"
#include "Vector2.h"

class MoveComponent;

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

    // Inherited via IInputListener
    void OnNotify(SDL_Event& pEvent) override;

private:
    float mInputZ; // Forward
    float mInputX; // Right
    MoveComponent* mMoveComponent; // Reference to the MoveComponent
};

