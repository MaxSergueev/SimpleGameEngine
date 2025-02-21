#pragma once
#include "IInputListener.h"
#include <vector>
class InputEvent
{
public:
	InputEvent() = default;
	~InputEvent();

	void Subscribe(IInputListener* pListener);

	void Unsubscribe(IInputListener* pListener);

	void NotifyListeners(SDL_Event& pEvent) const;

	std::vector<IInputListener*> mListeners;


};

