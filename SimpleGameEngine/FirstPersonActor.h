#pragma once
#include "Camera.h"

class FirstPersonActor : public Camera
{
public:
    FirstPersonActor(Scene* scene);
	~FirstPersonActor() override = default;
};

