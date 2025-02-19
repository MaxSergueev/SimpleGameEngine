#pragma once
#include <SDL_rect.h>
#include "Vector2.h"

struct Rectangle
{
    Vector2 position;
    Vector2 dimensions;

    SDL_Rect ToSdlRect() const
    {
        return SDL_Rect{
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            static_cast<int>(dimensions.x),
            static_cast<int>(dimensions.y)};
    }

    friend bool operator==(const Rectangle& left, const Rectangle& right)
    {
        return left.position.x == right.position.x
            && left.position.y == right.position.y
            && left.dimensions.x == right.dimensions.x
            && left.dimensions.y == right.dimensions.y;
    }

    friend bool operator!=(const Rectangle& left, const Rectangle& right)
    {
        return !(left == right);
    }
    static const Rectangle NullRect;
};
