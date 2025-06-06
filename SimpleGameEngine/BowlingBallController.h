#pragma once
#include "Component.h"
#include "IInputListener.h"
#include "Vector2.h"
#include "BowlingBall.h"

/**
 * @brief Input controller component for bowling ball mechanics
 *
 * BowlingBallController provides keyboard input handling for bowling ball gameplay,
 * allowing players to position the ball laterally before rolling and then launch
 * it forward. It implements a two-phase control system: positioning phase (left/right
 * movement within limits) and rolling phase (triggered by spacebar). Once rolled,
 * lateral movement is disabled to simulate realistic bowling physics.
 */
class BowlingBallController : public Component, public IInputListener
{
public:
    BowlingBallController() = delete;
    BowlingBallController(const BowlingBallController&) = delete;
    BowlingBallController& operator= (const BowlingBallController&) = delete;

    /**
     * @brief Constructs controller for the specified bowling ball
     * @param ball Pointer to the bowling ball to control
     */
    BowlingBallController(BowlingBall* ball);

    /**
     * @brief Destructor - unsubscribes from input events
     */
    ~BowlingBallController();

    /**
     * @brief Initializes input subscriptions for keyboard controls
     */
    void OnStart() override;

    /**
     * @brief Updates ball position based on input (only when not rolling)
     */
    void Update() override;

    /**
     * @brief Handles keyboard input events for ball control
     * @param pEvent SDL event containing input information
     */
    void OnNotify(SDL_Event& pEvent) override;

private:
    BowlingBall* mBowlingBall;  ///< Reference to the controlled bowling ball
    float mInputX;              ///< Current lateral input (-1.0 to 1.0)
    bool mIsRolling;            ///< Whether ball has been launched forward
    float mLateralLimit;        ///< Maximum lateral movement distance from center
};
