#pragma once

#define TINYOBJLOADER_IMPLEMENTATION

#include <map>
#include <string>
#include "Texture.h"
#include "Shader.h"
#include "ShaderProgram.h"

class Mesh;

//SINGLETON CLASS
class Assets
{
public:
    //Storage for future References
    static std::map<std::string, Texture> mTextures;
    static std::map<std::string, Mesh> mMeshes;
    static std::map<std::string, ShaderProgram> mShaderPrograms;
    
    static Texture LoadTexture(IRenderer& pRenderer, const std::string& pFileName, const std::string& pName);
    static Texture& GetTexture(const std::string& pName);
    static void Clear();

    static ShaderProgram* LoadShaderProgram(const std::string& pVert, const std::string& pFrag, const std::string& pName);
    static ShaderProgram& GetShaderProgram(const std::string& pName);

    static Mesh LoadMesh(const std::string& pFileName, const std::string& pName);
    static Mesh& GetMesh(const std::string& pName);

private:
    Assets() = default;
    static Texture LoadTextureFromFile(IRenderer& pRenderer, const std::string& pFileName);
    static Mesh LoadMeshFromFile(const std::string& pFileName);
};
