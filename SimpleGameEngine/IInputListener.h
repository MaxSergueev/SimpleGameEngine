#pragma once
#include "SDL_events.h"

class IInputListener
{
public:
	virtual ~IInputListener() = default;
	virtual void OnNotify(SDL_Event& pEvent) = 0;
};

