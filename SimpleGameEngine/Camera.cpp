#include "Camera.h"
#include <sstream>
#include "Log.h"
#include "Scene.h"

void Camera::UpdateActor()
{
	Actor::UpdateActor();

	SDL_GetRelativeMouseState(&mMouseDeltaX, &mMouseDeltaY);

	// Yaw
	this->RotateY(mMouseDeltaX/5);

	// Pitch
	p += Vector3(0, -mMouseDeltaY/5, 0);
	if (abs(p.y) > pitchLimit) {
		p.y = (p.y > 0) ? pitchLimit : -pitchLimit;
	}

	Vector3 camPosition = mTransform.GetPosition();
	Vector3 target = mTransform.GetPosition() + mTransform.Forward() * 100.0f + p;
	Vector3 up = Vector3::unitY;
	// Log::Info("" + std::to_string(camPosition.x) + ", " + std::to_string(camPosition.y) + ", " + std::to_string(camPosition.z));
	Matrix4Row view = Matrix4Row::CreateLookAt(camPosition, target, up);
	mScene.GetRenderer().SetViewMatrix(view);
}

