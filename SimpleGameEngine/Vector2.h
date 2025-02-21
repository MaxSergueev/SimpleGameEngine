#pragma once

struct Vector2
{
    float x, y;
    Vector2(float pX = 0, float pY = 0):x(pX), y(pY){}
    ~Vector2()=default;

    static const Vector2 Zero;
    static const Vector2 One;

    float GetSqrLength();

    friend Vector2 operator+(const Vector2& pLeft, const Vector2& pRight)
    {
        return {pLeft.x + pRight.x, pLeft.y + pRight.y};
    }
    friend Vector2 operator-(const Vector2& pLeft, const Vector2& pRight)
    {
        return {pLeft.x - pRight.x, pLeft.y - pRight.y};
    }
    friend Vector2 operator*(const Vector2& pLeft, const Vector2& pRight)
    {
        return {pLeft.x * pRight.x, pLeft.y * pRight.y};
    }
    friend Vector2 operator*(float pScalar, const Vector2& pRight)
    {
        return {pScalar * pRight.x, pScalar * pRight.y};
    }
    friend Vector2 operator*(const Vector2& pLeft, float pScalar)
    {
        return {pScalar * pLeft.x, pScalar * pLeft.y};
    }
    friend Vector2 operator/(const Vector2& pLeft, float pScalar)
    {
        return {pLeft.x/pScalar, pLeft.y/pScalar};
    }

    Vector2& operator+=(const Vector2& right)
    {
        x += right.x;
        y += right.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& right)
    {
        x -= right.x;
        y -= right.y;
        return *this;
    }

    Vector2& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vector2& operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }
};
