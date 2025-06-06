#include "Camera.h"
#include <sstream>
#include "Log.h"
#include "Scene.h"

void Camera::UpdateActor()
{
    Actor::UpdateActor();

    SDL_GetRelativeMouseState(&mMouseDeltaX, &mMouseDeltaY);

    this->RotateY(mMouseDeltaX / 5);

    p += Vector3(0, -mMouseDeltaY / 5, 0);
    if (abs(p.y) > pitchLimit) {
        p.y = (p.y > 0) ? pitchLimit : -pitchLimit;
    }

    Vector3 camPosition = mTransform.GetPosition();
    Vector3 target = mTransform.GetPosition() + mTransform.Forward() * 100.0f + p;
    Vector3 up = Vector3::unitY;

    Matrix4Row view = Matrix4Row::CreateLookAt(camPosition, target, up);
    mScene.GetRenderer().SetViewMatrix(view);
}


