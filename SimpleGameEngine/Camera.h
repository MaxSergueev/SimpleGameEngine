#pragma once
#include "Actor.h"

/**
 * @brief First-person camera controller with mouse look functionality
 *
 * Camera extends Actor to provide first-person camera controls using mouse input.
 * It handles mouse delta movement for yaw and pitch rotation with configurable
 * pitch limits and automatically updates the renderer's view matrix.
 */
class Camera : public Actor
{
private:
    /**
     * @brief Updates camera rotation and view matrix based on mouse input
     */
    void UpdateActor() override;

public:
    int mMouseDeltaX;       ///< Mouse movement delta on X axis (horizontal)
    int mMouseDeltaY;       ///< Mouse movement delta on Y axis (vertical)
    Vector3 p;              ///< Pitch accumulator vector
    int pitchLimit;         ///< Maximum pitch angle in degrees

    /**
     * @brief Default constructor - initializes pitch vector and limit
     */
    Camera() : p(Vector3(0, 0, 0)), pitchLimit(360) {}
};


