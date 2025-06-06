#pragma once
#include "MoveComponent.h"
#include "IInputListener.h"

/**
 * @brief Player input controller that extends MoveComponent with keyboard input handling
 *
 * PlayerController combines movement functionality with input listening to provide
 * player-controlled movement. It responds to WASD keys for directional movement
 * and automatically flips sprite orientation based on horizontal movement direction.
 * Inherits from both MoveComponent for movement and IInputListener for input handling.
 */
class PlayerController : public MoveComponent, public IInputListener
{
public:
    PlayerController() = delete;
    PlayerController(const PlayerController&) = delete;
    PlayerController& operator= (const MoveComponent&) = delete;

    /**
     * @brief Constructs a player controller for the specified actor
     * @param actor The actor to control with player input
     */
    PlayerController(Actor* actor);

    /**
     * @brief Destructor - unsubscribes from all input events
     */
    ~PlayerController();

    /**
     * @brief Initializes input subscriptions for WASD movement keys
     */
    void OnStart() override;

    /**
     * @brief Handles keyboard input events for player movement
     * @param pEvent The SDL input event to process
     */
    void OnNotify(SDL_Event& pEvent) override;

private:
    float mInputY;  ///< Vertical input component (W/S keys)
    float mInputX;  ///< Horizontal input component (A/D keys)
};
