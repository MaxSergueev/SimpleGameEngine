#pragma once

class Time
{
public:
    Time() = default;
    Time(const Time&) = delete;
    Time& operator=(const Time&) = delete;

    static unsigned int ComputeDeltaTime();
    static void DelayTime();

    static float deltaTime;

private:
    const static unsigned int FPS = 60;
    const static unsigned int FRAME_DELAY = 1000 / FPS;
    const static unsigned int MAX_DT = 50; //Maximum Delta Time


    static unsigned int mFrameStart;   //Time when current frame started
    static unsigned int mLastFrame;    //Last frame start time
    static unsigned int mFrameTime;    //Time needed to run the loop
};
