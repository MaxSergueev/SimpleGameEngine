#include "Camera.h"
#include <sstream>
#include "Log.h"
#include "Scene.h"

void Camera::UpdateActor()
{
	Actor::UpdateActor();
	Vector3 camPosition = mTransform.GetPosition();
	Vector3 target = mTransform.GetPosition() + mTransform.Forward() * 100.0f;
	Vector3 up = Vector3::unitZ;
	Log::Info("" + std::to_string(camPosition.x) + ", " + std::to_string(camPosition.y) + ", " + std::to_string(camPosition.z));
	Matrix4Row view = Matrix4Row::CreateLookAt(Vector3(0.0f, 0.0f, 0.0f), target, up);
	mScene.GetRenderer().SetViewMatrix(view);
}

