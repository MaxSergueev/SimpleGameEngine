#pragma once
#include <map>
#include "InputEvent.h"

class InputManager
{
    std::map<SDL_Keycode, InputEvent*> mKeyboardEvents;
    std::map<Uint8, InputEvent*> mMouseEvents; // For mouse buttons

public:
    InputManager() = default;
    ~InputManager();
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    static InputManager& Instance();
    void HandleInputs(SDL_Event& pEvent);

    // Keyboard events
    void SubscribeTo(SDL_Keycode pKeyCode, IInputListener* pListener);
    void UnsubscribeTo(SDL_Keycode pKeyCode, IInputListener* pListener);

    // Mouse events
    void SubscribeToMouse(Uint8 mouseButton, IInputListener* pListener);
    void UnsubscribeToMouse(Uint8 mouseButton, IInputListener* pListener);
};


