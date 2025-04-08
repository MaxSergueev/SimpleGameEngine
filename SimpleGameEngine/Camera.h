#pragma once
#include "Actor.h"

class Camera : public Actor
{
	void UpdateActor();

	public:
	int mMouseDeltaX;
	int mMouseDeltaY;

	Vector3 p = Vector3(0, 0, 0);
	int pitchLimit = 360;


};

