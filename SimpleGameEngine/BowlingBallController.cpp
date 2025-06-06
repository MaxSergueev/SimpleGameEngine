#include "BowlingBallController.h"
#include "InputManager.h"
#include <iostream>

BowlingBallController::BowlingBallController(BowlingBall* ball)
    : Component(ball), mBowlingBall(ball), mInputX(0.0f), mIsRolling(false), mLateralLimit(20.0f)
{
}

BowlingBallController::~BowlingBallController()
{
    InputManager::Instance().UnsubscribeTo(SDLK_SPACE, this);
    InputManager::Instance().UnsubscribeTo(SDLK_LEFT, this);
    InputManager::Instance().UnsubscribeTo(SDLK_RIGHT, this);
}

void BowlingBallController::OnStart()
{
    InputManager::Instance().SubscribeTo(SDLK_SPACE, this);
    InputManager::Instance().SubscribeTo(SDLK_LEFT, this);
    InputManager::Instance().SubscribeTo(SDLK_RIGHT, this);
}

void BowlingBallController::Update()
{
    if (!mIsRolling)
    {
        Vector3 currentPos = mOwner->GetTransform().GetPosition();

        float newX = currentPos.x + mInputX * 0.25f;

        if (newX < -mLateralLimit) newX = -mLateralLimit;
        if (newX > mLateralLimit) newX = mLateralLimit;

        mOwner->SetPosition(Vector3(newX, currentPos.y, currentPos.z));
    }
}

void BowlingBallController::OnNotify(SDL_Event& pEvent)
{
    if (pEvent.type == SDL_KEYDOWN || pEvent.type == SDL_KEYUP)
    {
        if (!mIsRolling || pEvent.key.keysym.sym == SDLK_SPACE)
        {
            switch (pEvent.key.keysym.sym)
            {
            case SDLK_LEFT:
                if (pEvent.type == SDL_KEYDOWN)
                    mInputX = -1.0f;
                else if (pEvent.type == SDL_KEYUP && mInputX < 0.0f)
                    mInputX = 0.0f;
                break;

            case SDLK_RIGHT:
                if (pEvent.type == SDL_KEYDOWN)
                    mInputX = 1.0f;
                else if (pEvent.type == SDL_KEYUP && mInputX > 0.0f)
                    mInputX = 0.0f;
                break;

            case SDLK_SPACE:
                if (pEvent.type == SDL_KEYDOWN && !mIsRolling)
                {
                    mIsRolling = true;
                    mBowlingBall->Roll(Vector2(0.0f, 1.0f));
                }
                break;
            }
        }
    }
}
