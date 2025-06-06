#pragma once

/**
 * @brief Static utility class for frame timing and delta time management
 *
 * Time provides frame rate control and delta time calculations for consistent
 * game loop timing. It manages frame delays to maintain target FPS and calculates
 * delta time between frames for frame-rate independent animations and physics.
 * Uses SDL timing functions for cross-platform compatibility.
 */
class Time
{
public:
    /**
     * @brief Default constructor
     */
    Time() = default;

    Time(const Time&) = delete;
    Time& operator=(const Time&) = delete;

    /**
     * @brief Calculates time elapsed since the last frame
     * @return Delta time in milliseconds (clamped to MAX_DT)
     */
    static unsigned int ComputeDeltaTime();

    /**
     * @brief Delays execution to maintain target frame rate
     */
    static void DelayTime();

    static float deltaTime;  ///< Time elapsed since last frame in seconds

private:
    const static unsigned int FPS = 60;         ///< Target frames per second
    const static unsigned int FRAME_DELAY = 1000 / FPS;  ///< Target milliseconds per frame
    const static unsigned int MAX_DT = 50;      ///< Maximum delta time to prevent large jumps

    static unsigned int mFrameStart;   ///< Timestamp when current frame started
    static unsigned int mLastFrame;    ///< Timestamp when previous frame started
    static unsigned int mFrameTime;    ///< Time taken to process current frame
};