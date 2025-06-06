#pragma once
#include "IInputListener.h"
#include <vector>

/**
 * @brief Manages a collection of input listeners for a specific input event
 *
 * InputEvent implements the observer pattern for input handling, maintaining
 * a list of listeners that should be notified when a specific input event
 * occurs. It provides subscription management and event broadcasting functionality.
 */
class InputEvent
{
public:
    /**
     * @brief Default constructor
     */
    InputEvent() = default;

    /**
     * @brief Destructor - clears all listener subscriptions
     */
    ~InputEvent();

    /**
     * @brief Subscribes a listener to receive notifications for this event
     * @param pListener The listener to add to the notification list
     */
    void Subscribe(IInputListener* pListener);

    /**
     * @brief Unsubscribes a listener from receiving notifications
     * @param pListener The listener to remove from the notification list
     */
    void Unsubscribe(IInputListener* pListener);

    /**
     * @brief Notifies all subscribed listeners of an input event
     * @param pEvent The SDL event to broadcast to all listeners
     */
    void NotifyListeners(SDL_Event& pEvent) const;

    std::vector<IInputListener*> mListeners;    ///< Collection of subscribed listeners

};
