#pragma once
#include <string>
#include <SDL_log.h>

/**
 * @brief Enumeration for different log message categories
 *
 * LogType maps to SDL log categories to provide consistent logging
 * across different engine systems and components.
 */
enum class LogType
{
    Application = SDL_LOG_CATEGORY_APPLICATION, ///< General application messages
    Assert = SDL_LOG_CATEGORY_ASSERT,           ///< Assertion failures
    Audio = SDL_LOG_CATEGORY_AUDIO,             ///< Audio system messages
    Error = SDL_LOG_CATEGORY_ERROR,             ///< Error messages
    Input = SDL_LOG_CATEGORY_INPUT,             ///< Input system messages
    Render = SDL_LOG_CATEGORY_RENDER,           ///< Rendering system messages
    System = SDL_LOG_CATEGORY_SYSTEM,           ///< System-level messages
    Test = SDL_LOG_CATEGORY_TEST,               ///< Testing and debugging messages
    Video = SDL_LOG_CATEGORY_VIDEO              ///< Video system messages
};

/**
 * @brief Static utility class for logging messages throughout the engine
 *
 * Log provides a centralized logging interface that wraps SDL's logging
 * functionality. It supports different log levels and categories for
 * organized message output and debugging.
 */
class Log
{
public:
    Log() = delete;
    Log(const Log&) = delete;
    Log& operator=(const Log&) = delete;

    /**
     * @brief Logs an informational message
     * @param message The message string to log
     */
    static void Info(const std::string& message);

    /**
     * @brief Logs an error message with category and SDL error information
     * @param category The log category for organizing error types
     * @param message The error message to log
     */
    static void Error(LogType category, const std::string& message);
};