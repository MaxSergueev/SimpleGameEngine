#include "InputManager.h"

#include "Log.h"

InputManager::~InputManager()
{
    std::map<SDL_Keycode, InputEvent*>::iterator it;
    for (it = mInputEvents.begin(); it != mInputEvents.end(); it++)
    {
        delete (it->second);
    }
    mInputEvents.clear();
}

//C++ implementation of the singleton
InputManager& InputManager::Instance()
{
    static InputManager instance;
    return instance;
}

void InputManager::HandleInputs(SDL_Event& pEvent)
{
    std::map<SDL_Keycode, InputEvent*>::iterator it = mInputEvents.find(pEvent.key.keysym.sym);
    if (it != mInputEvents.end())
    {
        (*it).second->NotifyListeners(pEvent);
    }
}

void InputManager::SubscribeTo(SDL_Keycode pKeyCode, IInputListener* pListener)
{
    //The count function of map<T,U> returns 1 if the element exists, 0 otherwise
    size_t hasKey = mInputEvents.count(pKeyCode);
    if (hasKey == 0)
    {
        mInputEvents[pKeyCode] = new InputEvent();
    }
    mInputEvents[pKeyCode]->Subscribe(pListener);
}

void InputManager::UnsubscribeTo(SDL_Keycode pKeyCode, IInputListener* pListener)
{
    ////Is this how you implement this? ////////////////////////////////////////////////////
    size_t hasKey = mInputEvents.count(pKeyCode);
    if (hasKey == 0)
    {
        mInputEvents[pKeyCode] = new InputEvent();
    }
    mInputEvents[pKeyCode]->Unsubscribe(pListener);
}

