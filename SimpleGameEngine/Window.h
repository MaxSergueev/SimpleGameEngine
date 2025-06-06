#pragma once
#include <SDL.h>
#include "Vector2.h"

/**
 * @brief SDL window wrapper for cross-platform window management
 *
 * Window encapsulates SDL window creation and management, providing a simple
 * interface for creating OpenGL-compatible windows. It handles SDL initialization,
 * window creation with specified dimensions, and proper cleanup of SDL resources.
 * The window is automatically configured for OpenGL rendering contexts.
 */
class Window
{
private:
    SDL_Window* mSdlWindow;  ///< SDL window handle for the created window
    Vector2 mDimensions;     ///< Window dimensions in pixels (width, height)

public:
    /**
     * @brief Constructs a window with specified dimensions
     * @param pWidth Width of the window in pixels
     * @param pHeight Height of the window in pixels
     */
    Window(int pWidth, int pHeight);

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    /**
     * @brief Gets the window dimensions
     * @return Vector2 containing width and height in pixels
     */
    Vector2 GetDimensions() const;

    /**
     * @brief Gets the underlying SDL window handle
     * @return Pointer to the SDL_Window object
     */
    SDL_Window* GetSdlWindow() const;

    /**
     * @brief Initializes SDL and creates the window
     * @return True if window creation was successful, false otherwise
     */
    bool Open();

    /**
     * @brief Destroys the window and releases SDL resources
     */
    void Close();
};
