#pragma once
#include "Component.h"
#include "IInputListener.h"
#include "Vector2.h"

class MoveComponent;
class FirstPersonActor;

/**
 * @brief First-person shooter input controller component
 *
 * FPSController handles WASD movement input and mouse shooting for first-person
 * characters. It integrates with the input system to provide responsive FPS controls
 * and automatically manages MoveComponent for character movement.
 */
class FPSController : public Component, public IInputListener
{
public:
    FPSController() = delete;
    FPSController(const FPSController&) = delete;
    FPSController& operator= (const FPSController&) = delete;

    /**
     * @brief Constructs an FPS controller for the specified actor
     * @param actor The actor to control (should be a FirstPersonActor for full functionality)
     */
    FPSController(Actor* actor);

    /**
     * @brief Destructor - unsubscribes from input events
     */
    ~FPSController();

    /**
     * @brief Initializes input subscriptions and mouse capture
     */
    void OnStart() override;

    /**
     * @brief Updates the controller (currently unused)
     */
    void Update() override;

    /**
     * @brief Handles input events for movement and shooting
     * @param pEvent The SDL event to process
     */
    void OnNotify(SDL_Event& pEvent) override;

private:
    float mInputZ;                      ///< Forward/backward input (-100 to 100)
    float mInputX;                      ///< Left/right strafe input (-100 to 100)
    MoveComponent* mMoveComponent;      ///< Movement component for applying input
    FirstPersonActor* mFirstPersonActor; ///< Reference for shooting functionality
};
