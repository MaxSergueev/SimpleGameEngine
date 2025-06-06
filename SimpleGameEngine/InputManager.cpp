#include "InputManager.h"
#include "Log.h"

InputManager::~InputManager()
{
    std::map<SDL_Keycode, InputEvent*>::iterator it;
    for (it = mKeyboardEvents.begin(); it != mKeyboardEvents.end(); it++)
    {
        delete (it->second);
    }
    mKeyboardEvents.clear();

    std::map<Uint8, InputEvent*>::iterator mouseIt;
    for (mouseIt = mMouseEvents.begin(); mouseIt != mMouseEvents.end(); mouseIt++)
    {
        delete (mouseIt->second);
    }
    mMouseEvents.clear();
}

InputManager& InputManager::Instance()
{
    static InputManager instance;
    return instance;
}

void InputManager::HandleInputs(SDL_Event& pEvent)
{
    if (pEvent.type == SDL_KEYDOWN || pEvent.type == SDL_KEYUP)
    {
        std::map<SDL_Keycode, InputEvent*>::iterator it = mKeyboardEvents.find(pEvent.key.keysym.sym);
        if (it != mKeyboardEvents.end())
        {
            (*it).second->NotifyListeners(pEvent);
        }
    }
    else if (pEvent.type == SDL_MOUSEBUTTONDOWN || pEvent.type == SDL_MOUSEBUTTONUP)
    {
        std::map<Uint8, InputEvent*>::iterator it = mMouseEvents.find(pEvent.button.button);
        if (it != mMouseEvents.end())
        {
            (*it).second->NotifyListeners(pEvent);
        }
    }
}

void InputManager::SubscribeTo(SDL_Keycode pKeyCode, IInputListener* pListener)
{
    size_t hasKey = mKeyboardEvents.count(pKeyCode);
    if (hasKey == 0)
    {
        mKeyboardEvents[pKeyCode] = new InputEvent();
    }
    mKeyboardEvents[pKeyCode]->Subscribe(pListener);
}

void InputManager::UnsubscribeTo(SDL_Keycode pKeyCode, IInputListener* pListener)
{
    size_t hasKey = mKeyboardEvents.count(pKeyCode);
    if (hasKey == 0)
    {
        mKeyboardEvents[pKeyCode] = new InputEvent();
    }
    mKeyboardEvents[pKeyCode]->Unsubscribe(pListener);
}

void InputManager::SubscribeToMouse(Uint8 mouseButton, IInputListener* pListener)
{
    size_t hasKey = mMouseEvents.count(mouseButton);
    if (hasKey == 0)
    {
        mMouseEvents[mouseButton] = new InputEvent();
    }
    mMouseEvents[mouseButton]->Subscribe(pListener);
}

void InputManager::UnsubscribeToMouse(Uint8 mouseButton, IInputListener* pListener)
{
    size_t hasKey = mMouseEvents.count(mouseButton);
    if (hasKey == 0)
    {
        mMouseEvents[mouseButton] = new InputEvent();
    }
    mMouseEvents[mouseButton]->Unsubscribe(pListener);
}
