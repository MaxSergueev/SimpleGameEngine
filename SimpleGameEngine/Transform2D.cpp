#include "Transform2D.h"
#include "Matrix4Row.h"

Transform2D::Transform2D():mPosition(0, 0, 0), mScale(1, 1, 1), mRotation(Quaternion::Identity), mNeedsUpdate(true)
{
}

void Transform2D::Translate(Vector3 pMovement)
{
    mPosition += pMovement;
}

void Transform2D::Rotate(float pRotation)
{
}

void Transform2D::ComputeWorldTransform()
{
    if (!mNeedsUpdate) return;
    mNeedsUpdate = false;
    mWorldTransform = Matrix4Row::CreateScale(mScale);
    mWorldTransform *= Matrix4Row::CreateFromQuaternion(mRotation);
    mWorldTransform *= Matrix4Row::CreateTranslation(mPosition);
}


