#pragma once
#include <SDL_rect.h>
#include "Vector2.h"

/**
 * @brief 2D rectangle structure for UI and sprite rendering
 *
 * Rectangle represents a 2D rectangular area defined by position and dimensions.
 * It provides conversion utilities for SDL rendering and comparison operators
 * for rectangle equality testing. Used primarily for sprite source rectangles
 * and UI element positioning.
 */
struct Rectangle
{
    Vector2 position;    ///< Top-left corner position of the rectangle
    Vector2 dimensions;  ///< Width and height of the rectangle

    /**
     * @brief Converts the rectangle to SDL_Rect format for rendering
     * @return SDL_Rect structure with integer coordinates
     */
    SDL_Rect ToSdlRect() const
    {
        return SDL_Rect{
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            static_cast<int>(dimensions.x),
            static_cast<int>(dimensions.y) };
    }

    /**
     * @brief Equality comparison operator
     * @param left First rectangle to compare
     * @param right Second rectangle to compare
     * @return True if both position and dimensions are equal
     */
    friend bool operator==(const Rectangle& left, const Rectangle& right)
    {
        return left.position.x == right.position.x
            && left.position.y == right.position.y
            && left.dimensions.x == right.dimensions.x
            && left.dimensions.y == right.dimensions.y;
    }

    /**
     * @brief Inequality comparison operator
     * @param left First rectangle to compare
     * @param right Second rectangle to compare
     * @return True if position or dimensions are not equal
     */
    friend bool operator!=(const Rectangle& left, const Rectangle& right)
    {
        return !(left == right);
    }

    static const Rectangle NullRect;  ///< Predefined null rectangle (0,0,0,0)
};

