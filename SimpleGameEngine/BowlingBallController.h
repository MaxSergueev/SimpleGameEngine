#pragma once
#include "Component.h"
#include "IInputListener.h"
#include "Vector2.h"
#include "BowlingBall.h"

class BowlingBallController : public Component, public IInputListener
{
public:
    BowlingBallController() = delete;
    BowlingBallController(const BowlingBallController&) = delete;
    BowlingBallController& operator= (const BowlingBallController&) = delete;

    BowlingBallController(BowlingBall* ball);
    ~BowlingBallController();

    void OnStart() override;
    void Update() override;

    void OnNotify(SDL_Event& pEvent) override;

private:
    BowlingBall* mBowlingBall;
    float mInputX;
    bool mIsRolling;
    float mLateralLimit;
};

