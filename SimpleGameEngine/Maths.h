#pragma once

#include <limits>
#include <cmath>

/**
 * @brief Mathematical utility functions and constants for the game engine
 *
 * The Maths namespace provides commonly used mathematical constants,
 * conversion functions, and utility operations for game development.
 * All functions are inlined for performance optimization.
 */
namespace Maths
{
    const float PI = 3.1415926535f;                             ///< Mathematical constant Pi
    const float TWO_PI = PI * 2.0f;                            ///< Two times Pi (full circle in radians)
    const float PI_HALVED = PI / 2.0f;                         ///< Pi divided by 2 (quarter circle in radians)
    const float INFINITY_POS = std::numeric_limits<float>::infinity(); ///< Positive infinity value
    const float INFINITY_NEG = -INFINITY_POS;                  ///< Negative infinity value

    /**
     * @brief Converts degrees to radians
     * @param degrees Angle in degrees
     * @return Angle in radians
     */
    inline float ToRad(float degrees) { return degrees * PI / 180.0f; }

    /**
     * @brief Converts radians to degrees
     * @param radians Angle in radians
     * @return Angle in degrees
     */
    inline float ToDeg(float radians) { return radians * 180.0f / PI; }

    /**
     * @brief Checks if a value is near zero within epsilon tolerance
     * @param val The value to test
     * @param epsilon The tolerance for comparison (default: 0.001f)
     * @return True if the absolute value is less than or equal to epsilon
     */
    inline bool NearZero(float val, float epsilon = 0.001f) { return fabs(val) <= epsilon; }

    /**
     * @brief Returns the maximum of two values
     * @tparam T Type of values to compare
     * @param a First value
     * @param b Second value
     * @return The larger of the two values
     */
    template<typename T>
    T Max(const T& a, const T& b) { return a < b ? b : a; }

    /**
     * @brief Returns the minimum of two values
     * @tparam T Type of values to compare
     * @param a First value
     * @param b Second value
     * @return The smaller of the two values
     */
    template<typename T>
    T Min(const T& a, const T& b) { return a < b ? a : b; }

    /**
     * @brief Clamps a value between lower and upper bounds
     * @tparam T Type of values to clamp
     * @param val The value to clamp
     * @param lower The minimum allowed value
     * @param upper The maximum allowed value
     * @return The clamped value within the specified range
     */
    template<typename T>
    T Clamp(const T& val, const T& lower, const T& upper) { return Min(upper, Max(val, lower)); }

    /**
     * @brief Returns the absolute value of a float
     * @param val The value to get absolute value of
     * @return The absolute value
     */
    inline float Abs(float val) { return fabs(val); }

    /**
     * @brief Calculates the cosine of an angle
     * @param angle Angle in radians
     * @return Cosine of the angle
     */
    inline float Cos(float angle) { return cosf(angle); }

    /**
     * @brief Calculates the sine of an angle
     * @param angle Angle in radians
     * @return Sine of the angle
     */
    inline float Sin(float angle) { return sinf(angle); }

    /**
     * @brief Calculates the tangent of an angle
     * @param angle Angle in radians
     * @return Tangent of the angle
     */
    inline float Tan(float angle) { return tanf(angle); }

    /**
     * @brief Calculates the arc cosine of a value
     * @param angle Value between -1 and 1
     * @return Arc cosine in radians
     */
    inline float ACos(float angle) { return acosf(angle); }

    /**
     * @brief Calculates the arc tangent of y/x
     * @param opposite The opposite side (y component)
     * @param adjacent The adjacent side (x component)
     * @return Arc tangent in radians, properly handling quadrants
     */
    inline float ATan2(float opposite, float adjacent) { return atan2f(opposite, adjacent); }

    /**
     * @brief Calculates the cotangent of an angle
     * @param angle Angle in radians
     * @return Cotangent of the angle (1/tan)
     */
    inline float Cot(float angle) { return 1.0f / Tan(angle); }

    /**
     * @brief Performs linear interpolation between two values
     * @param a Starting value
     * @param b Ending value
     * @param t Interpolation factor (0.0 to 1.0)
     * @return Interpolated value between a and b
     */
    inline float Lerp(float a, float b, float t) { return a + t * (b - a); }

    /**
     * @brief Calculates the square root of a value
     * @param val The value to get square root of
     * @return Square root of the value
     */
    inline float Sqrt(float val) { return sqrtf(val); }

    /**
     * @brief Calculates the floating-point remainder of division
     * @param numer The numerator
     * @param denom The denominator
     * @return The floating-point remainder of numer/denom
     */
    inline float Fmod(float numer, float denom) { return std::fmod(numer, denom); }

    /**
     * @brief Rounds a float to the nearest integer
     * @param val The value to round
     * @return The rounded integer value
     */
    inline int Round(float val) { return static_cast<int>(val); }
}

