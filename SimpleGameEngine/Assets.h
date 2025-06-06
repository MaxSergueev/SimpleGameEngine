#pragma once

#define TINYOBJLOADER_IMPLEMENTATION

#include <map>
#include <string>
#include "Texture.h"
#include "Shader.h"
#include "ShaderProgram.h"

class Mesh;

/**
 * @brief Static asset management system for the engine
 *
 * The Assets class provides centralized loading, storage, and retrieval
 * of game assets including textures, meshes, and shader programs.
 * All assets are stored in static containers and can be accessed by name.
 */
class Assets
{
public:
    static std::map<std::string, Texture> mTextures;        ///< Storage for loaded textures
    static std::map<std::string, Mesh> mMeshes;             ///< Storage for loaded meshes
    static std::map<std::string, ShaderProgram> mShaderPrograms;  ///< Storage for compiled shader programs

    /**
     * @brief Loads a texture from file and stores it with a name
     * @param pRenderer The renderer to use for texture loading
     * @param pFileName Path to the texture file
     * @param pName Unique name to identify the texture
     * @return The loaded texture
     */
    static Texture LoadTexture(IRenderer& pRenderer, const std::string& pFileName, const std::string& pName);

    /**
     * @brief Retrieves a previously loaded texture by name
     * @param pName The name of the texture to retrieve
     * @return Reference to the requested texture
     */
    static Texture& GetTexture(const std::string& pName);

    /**
     * @brief Clears all loaded assets and frees memory
     */
    static void Clear();

    /**
     * @brief Loads and compiles a shader program from vertex and fragment shaders
     * @param pVert Path to the vertex shader file
     * @param pFrag Path to the fragment shader file
     * @param pName Unique name to identify the shader program
     * @return Pointer to the compiled shader program
     */
    static ShaderProgram* LoadShaderProgram(const std::string& pVert, const std::string& pFrag, const std::string& pName);

    /**
     * @brief Retrieves a previously loaded shader program by name
     * @param pName The name of the shader program to retrieve
     * @return Reference to the requested shader program
     */
    static ShaderProgram& GetShaderProgram(const std::string& pName);

    /**
     * @brief Loads a mesh from an OBJ file and stores it with a name
     * @param pFileName Path to the mesh file (.obj format)
     * @param pName Unique name to identify the mesh
     * @return The loaded mesh
     */
    static Mesh LoadMesh(const std::string& pFileName, const std::string& pName);

    /**
     * @brief Retrieves a previously loaded mesh by name
     * @param pName The name of the mesh to retrieve
     * @return Reference to the requested mesh
     */
    static Mesh& GetMesh(const std::string& pName);

private:
    /**
     * @brief Private constructor - this is a static utility class
     */
    Assets() = default;

    /**
     * @brief Internal method to load texture from file
     * @param pRenderer The renderer to use for loading
     * @param pFileName Path to the texture file
     * @return The loaded texture
     */
    static Texture LoadTextureFromFile(IRenderer& pRenderer, const std::string& pFileName);

    /**
     * @brief Internal method to load mesh from OBJ file
     * @param pFileName Path to the OBJ file
     * @return The loaded mesh
     */
    static Mesh LoadMeshFromFile(const std::string& pFileName);
};

