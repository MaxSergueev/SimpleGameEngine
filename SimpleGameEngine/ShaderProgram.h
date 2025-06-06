#pragma once
#include <glew.h>

#include "Shader.h"
#include <vector>

#include "Matrix4Row.h"
#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

/**
 * @brief OpenGL shader program wrapper for managing linked shader pipelines
 *
 * ShaderProgram encapsulates OpenGL shader program objects, providing functionality
 * to link multiple shaders together and set uniform variables. It supports all
 * common uniform types including scalars, vectors, and matrices, with specialized
 * methods for tessellation control and matrix transformations.
 */
class ShaderProgram
{
private:
    unsigned int mId;   ///< OpenGL shader program object identifier

public:
    /**
     * @brief Default constructor - creates uninitialized shader program
     */
    ShaderProgram();

    /**
     * @brief Default destructor
     */
    ~ShaderProgram() = default;

    /**
     * @brief Releases OpenGL shader program resources
     */
    void Unload();

    /**
     * @brief Links multiple shaders into a complete shader program
     * @param shaders Vector of shader pointers to link together
     */
    void Compose(std::vector<Shader*> shaders);

    /**
     * @brief Gets the OpenGL shader program ID
     * @return The OpenGL identifier for this shader program
     */
    unsigned int GetID();

    /**
     * @brief Activates this shader program for rendering
     */
    void Use();

    /**
     * @brief Sets a float uniform variable
     * @param name Name of the uniform variable in the shader
     * @param value Float value to set
     */
    void setFloat(const GLchar* name, GLfloat value);

    /**
     * @brief Sets an integer uniform variable
     * @param name Name of the uniform variable in the shader
     * @param value Integer value to set
     */
    void setInteger(const GLchar* name, GLint value);

    /**
     * @brief Sets a 2D vector uniform variable from components
     * @param name Name of the uniform variable in the shader
     * @param x X component of the vector
     * @param y Y component of the vector
     */
    void setVector2f(const GLchar* name, GLfloat x, GLfloat y);

    /**
     * @brief Sets a 2D vector uniform variable from Vector2 object
     * @param name Name of the uniform variable in the shader
     * @param value Vector2 object containing the values
     */
    void setVector2f(const GLchar* name, const Vector2& value);

    /**
     * @brief Sets a 3D vector uniform variable from components
     * @param name Name of the uniform variable in the shader
     * @param x X component of the vector
     * @param y Y component of the vector
     * @param z Z component of the vector
     */
    void setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z);

    /**
     * @brief Sets a 3D vector uniform variable from Vector3 object
     * @param name Name of the uniform variable in the shader
     * @param value Vector3 object containing the values
     */
    void setVector3f(const GLchar* name, const Vector3& value);

    /**
     * @brief Sets a 4D vector uniform variable from components
     * @param name Name of the uniform variable in the shader
     * @param x X component of the vector
     * @param y Y component of the vector
     * @param z Z component of the vector
     * @param w W component of the vector
     */
    void setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

    /**
     * @brief Sets a 4D vector uniform variable from Vector4 object
     * @param name Name of the uniform variable in the shader
     * @param value Vector4 object containing the values
     */
    void setVector4f(const GLchar* name, const Vector4& value);

    /**
     * @brief Sets a 4x4 matrix uniform variable (column-major)
     * @param name Name of the uniform variable in the shader
     * @param matrix Matrix4 object containing the transformation
     */
    void setMatrix4(const GLchar* name, const Matrix4& matrix);

    /**
     * @brief Sets a 4x4 matrix uniform variable (row-major)
     * @param name Name of the uniform variable in the shader
     * @param matrix Matrix4Row object containing the transformation
     */
    void setMatrix4Row(const GLchar* name, const Matrix4Row& matrix);

    /**
     * @brief Configures tessellation levels for tessellation shaders
     * @param inner Inner tessellation level
     * @param outer Outer tessellation level
     */
    void setTessellationLevels(float inner, float outer);
};
