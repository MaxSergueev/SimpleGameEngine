#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Maths.h"
#include "Matrix4Row.h"
#include "Matrix4.h"


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
    void SetPosition(Vector3 pPosition) {mPosition = pPosition;}
    void SetScale(Vector3 pScale){mScale = pScale;}
    void SetRotation(Quaternion pRotation) {mRotation = pRotation;}

    Vector3 GetPosition() const {return mPosition;}
    Vector3 GetScale() const {return mScale;}
    Quaternion GetRotation() const {return mRotation;}

    void Translate(Vector3 pMovement);
    void Rotate(float pRotation);

    void ComputeWorldTransform();
    Matrix4Row GetWorldTransform() { return mWorldTransform; }

    Vector3 Right() const { return Vector3(Maths::Cos(mRotation.z), -Maths::Sin(mRotation.z), 0); }
    Vector3 Up() const { return Vector3(Maths::Sin(mRotation.z), -Maths::Cos(mRotation.z), 0); }
    Vector3 Forward() const { return Vector3::Transform(Vector3::unitX, mRotation); }

};
