#pragma once
#include <SDL.h>
#include "Vector2.h"

class Window
{
private:
    SDL_Window* mSdlWindow;
    Vector2 mDimensions;
public:
    Window(int pWidth, int pHeight);
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Vector2 GetDimensions() const;

    SDL_Window* GetSdlWindow() const;

    bool Open();
    void Close();
};
