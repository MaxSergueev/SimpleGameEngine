#include "Transform2D.h"

Transform2D::Transform2D() :mPosition(0, 0, 0), mScale(1.0f, 1.0f, 1.0f),
mRotation(Quaternion::Identity), mNeedsUpdate(true)
{
}

void Transform2D::SetRotation(Vector3 pRotation)
{
    mRotation = Quaternion::Identity;

    if (pRotation.x != 0.0f) RotateX(pRotation.x);
    if (pRotation.y != 0.0f) RotateY(pRotation.y);
    if (pRotation.z != 0.0f) RotateZ(pRotation.z);

    mNeedsUpdate = true;
}

void Transform2D::Translate(Vector3 pMovement)
{
    mPosition += pMovement;
    mNeedsUpdate = true;
}

void Transform2D::RotateAroundAxis(Vector3 pAxis, float pAngle)
{
    Vector3 normalizedAxis = pAxis;
    float length = normalizedAxis.Length();
    if (length > 0.0f) {
        normalizedAxis.x /= length;
        normalizedAxis.y /= length;
        normalizedAxis.z /= length;
    }

    Quaternion qRotation(normalizedAxis, Maths::ToRad(pAngle));
    mRotation = Quaternion::Concatenate(mRotation, qRotation);
    mNeedsUpdate = true;
}

void Transform2D::Rotate(Vector3 pRotation)
{
    if (pRotation.x != 0.0f) RotateX(pRotation.x);
    if (pRotation.y != 0.0f) RotateY(pRotation.y);
    if (pRotation.z != 0.0f) RotateZ(pRotation.z);
}

void Transform2D::RotateX(float xRotation)
{
    Quaternion qRotation(Vector3(1.0f, 0.0f, 0.0f), Maths::ToRad(xRotation));
    mRotation = Quaternion::Concatenate(mRotation, qRotation);
    mNeedsUpdate = true;
}

void Transform2D::RotateY(float yRotation)
{
    Quaternion qRotation(Vector3(0.0f, 1.0f, 0.0f), Maths::ToRad(yRotation));
    mRotation = Quaternion::Concatenate(mRotation, qRotation);
    mNeedsUpdate = true;
}

void Transform2D::RotateZ(float zRotation)
{
    Quaternion qRotation(Vector3(0.0f, 0.0f, 1.0f), Maths::ToRad(zRotation));
    mRotation = Quaternion::Concatenate(mRotation, qRotation);
    mNeedsUpdate = true;
}

void Transform2D::ComputeWorldTransform()
{
    if (!mNeedsUpdate) return;
    mNeedsUpdate = false;
    mWorldTransform = Matrix4Row::CreateScale(mScale);
    mWorldTransform *= Matrix4Row::CreateFromQuaternion(mRotation);
    mWorldTransform *= Matrix4Row::CreateTranslation(mPosition);
}
