#pragma once
#include "Vector3.h"
#include "VertexArray.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Assets.h"

class VertexArray;

/**
 * @brief Structure representing a single vertex with position, normal, and texture coordinates
 *
 * Vertex contains all the data needed to render a point in 3D space,
 * including its position, surface normal for lighting calculations,
 * and texture coordinates for material mapping.
 */
struct Vertex
{
public:
    Vector3 position;   ///< 3D position of the vertex
    Vector3 normal;     ///< Surface normal vector for lighting
    Vector2 texCoord;   ///< Texture coordinates (UV mapping)
};

/**
 * @brief 3D mesh representation with vertices, textures, and shaders
 *
 * Mesh encapsulates a 3D model's geometry data, material textures,
 * and rendering shaders. It manages vertex data conversion for GPU
 * rendering and provides texture/shader management functionality.
 */
class Mesh
{
public:
    /**
     * @brief Default constructor - creates empty mesh with basic shaders
     */
    Mesh();

    /**
     * @brief Constructs mesh from vertex data
     * @param pVertices Vector of vertices defining the mesh geometry
     */
    Mesh(std::vector<Vertex> pVertices);

    /**
     * @brief Destructor
     */
    ~Mesh();

    /**
     * @brief Converts vertex data to flat array format for GPU rendering
     * @return Dynamically allocated float array (caller must delete)
     */
    float* ToVerticeArray();

    /**
     * @brief Releases GPU resources and cleans up vertex array
     */
    void Unload();

    /**
     * @brief Gets the shader program used for rendering this mesh
     * @return Reference to the mesh's shader program
     */
    ShaderProgram& GetShaderProgram();

    /**
     * @brief Sets a custom shader program for this mesh
     * @param pShader Pointer to the shader program to use
     */
    void SetShaderProgram(ShaderProgram* pShader);

    /**
     * @brief Gets a texture at the specified index
     * @param textureIndex Index of the texture to retrieve
     * @return Pointer to the texture, or nullptr if index is invalid
     */
    Texture* GetTexture(size_t textureIndex);

    /**
     * @brief Sets a texture at the specified index
     * @param texture Pointer to the texture to set
     * @param index Index where to store the texture (default: 0)
     */
    void SetTexture(Texture* texture, size_t index = 0);

    /**
     * @brief Gets the vertex array object for GPU rendering
     * @return Pointer to the vertex array object
     */
    VertexArray* GetVertexArray() { return mVertexArray; }

private:
    VertexArray* mVertexArray;              ///< GPU vertex array object
    Shader mVertexShader;                   ///< Vertex shader for rendering
    Shader mFragmentShader;                 ///< Fragment shader for rendering
    ShaderProgram mShaderProgram;           ///< Combined shader program
    std::vector<Texture*> mTextures;        ///< Collection of textures for materials
    std::vector<Vertex> mVertices;          ///< Original vertex data
};
