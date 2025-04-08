#pragma once
#include "Vector3.h"
#include "Matrix4Row.h"
#include "Maths.h"

class Transform2D
{
private:
    Vector3 mPosition;
    Vector3 mScale;
    Quaternion mRotation;
	Matrix4Row mWorldTransform;
    bool mNeedsUpdate;

public:
    Transform2D();

    ~Transform2D() = default;

    void SetPosition(Vector3 pPosition) { mPosition = pPosition; mNeedsUpdate = true; }
    void SetScale(Vector3 pScale) { mScale = pScale; mNeedsUpdate = true; }
    void SetRotation(Vector3 pRotation);

    Vector3 GetPosition() const { return mPosition; }
    Vector3 GetScale() const { return mScale; }
    Quaternion GetRotation() const { return mRotation; }
	Matrix4Row GetWorldTransform() const { return mWorldTransform; }

    void Translate(Vector3 pMovement);

	void RotateAroundAxis(Vector3 pAxis, float pAngle);
    void Rotate(Vector3 pRotation);
    void RotateX(float xRotation);
	void RotateY(float yRotation);
	void RotateZ(float zRotation);

    void ComputeWorldTransform();

    /*Vector3 Right() const { return Vector3(Maths::Cos(mRotation.z), -Maths::Sin(mRotation.z), 0.0f); }
    Vector3 Up() const { return Vector3(Maths::Sin(mRotation.z), Maths::Cos(mRotation.z), 0.0f); }*/
    Vector3 Right() const { return Vector3::Transform(Vector3::unitY, mRotation); }
    Vector3 Up() const { return Vector3::Transform(Vector3::unitZ, mRotation); }
    Vector3 Forward() const { return Vector3::Transform(Vector3::unitX, mRotation); }


};

