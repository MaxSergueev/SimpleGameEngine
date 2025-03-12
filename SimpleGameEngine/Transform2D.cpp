#include "Transform2D.h"

Transform2D::Transform2D() :mPosition(0, 0, 0), mScale( 1.0f, 1.0f, 1.0f), 
                            mRotation(0.0f, 0.0f, 0.0f), mNeedsUpdate(true)
{
}

void Transform2D::Translate(Vector3 pMovement)
{
    mPosition += pMovement;
    mNeedsUpdate = true;
}

void Transform2D::Rotate(Vector3 pRotation)
{
    mRotation += pRotation;
    mNeedsUpdate = true;
}

void Transform2D::ComputeWorldTransform()
{
    if (!mNeedsUpdate) return;
    mNeedsUpdate = false;
    mWorldTransform = Matrix4Row::CreateScale(mScale);
    mWorldTransform *= Matrix4Row::CreateRotationX(mRotation.x);
    mWorldTransform *= Matrix4Row::CreateRotationY(mRotation.y);
    mWorldTransform *= Matrix4Row::CreateRotationZ(mRotation.z);
    mWorldTransform *= Matrix4Row::CreateTranslation(mPosition);
    //mOwner->UpdateComponentsTransform();
}