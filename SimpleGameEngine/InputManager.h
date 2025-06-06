#pragma once
#include <map>
#include "InputEvent.h"

/**
 * @brief Singleton input management system for handling keyboard and mouse events
 *
 * InputManager provides centralized input event handling using the observer pattern.
 * It manages subscriptions for specific keys and mouse buttons, routing SDL events
 * to registered listeners. Implements singleton pattern for global access.
 */
class InputManager
{
private:
    std::map<SDL_Keycode, InputEvent*> mKeyboardEvents;  ///< Map of keyboard events by key code
    std::map<Uint8, InputEvent*> mMouseEvents;           ///< Map of mouse button events

public:
    InputManager() = default;

    /**
     * @brief Destructor - cleans up all input event objects
     */
    ~InputManager();

    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    /**
     * @brief Gets the singleton instance of InputManager
     * @return Reference to the singleton InputManager instance
     */
    static InputManager& Instance();

    /**
     * @brief Processes SDL events and notifies appropriate listeners
     * @param pEvent The SDL event to process and route
     */
    void HandleInputs(SDL_Event& pEvent);

    /**
     * @brief Subscribes a listener to a specific keyboard key
     * @param pKeyCode The SDL key code to listen for
     * @param pListener The listener to notify when the key event occurs
     */
    void SubscribeTo(SDL_Keycode pKeyCode, IInputListener* pListener);

    /**
     * @brief Unsubscribes a listener from a specific keyboard key
     * @param pKeyCode The SDL key code to stop listening for
     * @param pListener The listener to remove from notifications
     */
    void UnsubscribeTo(SDL_Keycode pKeyCode, IInputListener* pListener);

    /**
     * @brief Subscribes a listener to a specific mouse button
     * @param mouseButton The SDL mouse button to listen for
     * @param pListener The listener to notify when the mouse button event occurs
     */
    void SubscribeToMouse(Uint8 mouseButton, IInputListener* pListener);

    /**
     * @brief Unsubscribes a listener from a specific mouse button
     * @param mouseButton The SDL mouse button to stop listening for
     * @param pListener The listener to remove from notifications
     */
    void UnsubscribeToMouse(Uint8 mouseButton, IInputListener* pListener);
};
