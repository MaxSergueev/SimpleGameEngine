#include "Transform2D.h"

Transform2D::Transform2D():mPosition({0,0}), mScale({1, 1}), mZrotation(0.0f)
{
}

void Transform2D::Translate(Vector2 pMovement)
{
    mPosition += pMovement;
}

void Transform2D::Rotate(float pRotation)
{
    mZrotation += pRotation;
}
