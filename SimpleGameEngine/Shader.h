#pragma once
#include <string>
#include <fstream>

/**
 * @brief Enumeration of supported shader types for OpenGL rendering
 */
enum ShaderType {
    VERTEX,                     ///< Vertex shader for vertex processing
    FRAGMENT,                   ///< Fragment shader for pixel processing
    TESSELLATION_CONTROL,       ///< Tessellation control shader
    TESSELLATION_EVALUATION,    ///< Tessellation evaluation shader
    GEOMETRY                    ///< Geometry shader for primitive processing
};

/**
 * @brief OpenGL shader wrapper for loading and compiling shader programs
 *
 * Shader encapsulates OpenGL shader objects, providing functionality to load
 * shader source code from files, compile shaders, and manage shader resources.
 * Supports all major shader types including vertex, fragment, geometry, and
 * tessellation shaders for modern OpenGL rendering pipelines.
 */
class Shader
{
protected:
    std::string mCode;      ///< Source code of the shader
    unsigned int mId;       ///< OpenGL shader object identifier
    ShaderType mType;       ///< Type of shader (vertex, fragment, etc.)
    const char* mSource;    ///< Pointer to shader source code

public:
    static const std::string SHADER_PATH;  ///< Base path for shader files

    /**
     * @brief Default constructor - creates uninitialized shader
     */
    Shader();

    /**
     * @brief Constructs shader with specified parameters
     * @param pId OpenGL shader object ID
     * @param pCode Shader source code
     * @param pShaderType Type of shader to create
     */
    Shader(int pId, std::string pCode, ShaderType pShaderType);

    /**
     * @brief Destructor
     */
    ~Shader();

    /**
     * @brief Gets the OpenGL shader object ID
     * @return The OpenGL identifier for this shader
     */
    int GetID() const { return mId; }

    /**
     * @brief Loads and compiles shader from file
     * @param pFileName Name of the shader file (relative to SHADER_PATH)
     * @param pShaderType Type of shader to compile
     */
    void Load(std::string pFileName, ShaderType pShaderType);

    /**
     * @brief Gets the shader source code
     * @return Reference to the shader source code string
     */
    std::string& GetCode();
};
