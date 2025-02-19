#pragma once
#include "Vector2.h"


class Transform2D
{
private:
    Vector2 mPosition;
    Vector2 mScale;
    float mZrotation;
    
public:
    Transform2D();
    ~Transform2D() = default;
    void SetPosition(Vector2 pPosition) {mPosition = pPosition;}
    void SetScale(Vector2 pScale){mScale = pScale;}
    void SetRotation(float pRotation) {mZrotation = pRotation;}

    Vector2 GetPosition() const {return mPosition;}
    Vector2 GetScale() const {return mScale;}
    float GetRotation() const {return mZrotation;}

    void Translate(Vector2 pMovement);
    void Rotate(float pRotation);
};
