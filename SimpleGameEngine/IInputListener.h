#pragma once
#include "SDL_events.h"

/**
 * @brief Interface for objects that need to receive input events
 *
 * IInputListener provides a contract for classes that want to receive
 * and handle SDL input events through the observer pattern. Classes
 * implementing this interface can subscribe to specific input events
 * through the InputManager system.
 */
class IInputListener
{
public:
    /**
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~IInputListener() = default;

    /**
     * @brief Called when a subscribed input event occurs
     * @param pEvent The SDL event that was triggered
     */
    virtual void OnNotify(SDL_Event& pEvent) = 0;
};
