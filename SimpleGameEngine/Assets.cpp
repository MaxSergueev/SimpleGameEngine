#include "Assets.h"
#include <sstream>

#include "Log.h"
#include "MeshComponent.h"
#include "../Dependencies/tiny_obj_loader.h"

std::map<std::string, Texture> Assets::mTextures = {};
std::map<std::string, Mesh> Assets::mMeshes = {};
std::map < std::string, ShaderProgram> Assets::mShaderPrograms = {};

Texture Assets::LoadTexture(IRenderer& pRenderer, const std::string& pFileName, const std::string& pName)
{
    mTextures[pName] = LoadTextureFromFile(pRenderer, pFileName);
    return mTextures[pName];
}

Texture& Assets::GetTexture(const std::string& pName)
{
    if(mTextures.find(pName) == mTextures.end())
    {
        std::ostringstream loadError;
        loadError << "Texture "<<pName<<" does not exist in assets manager\n";
        Log::Error(LogType::Application, loadError.str());
    }
    return mTextures[pName];
}

void Assets::Clear()
{
    for(auto iter : mTextures)
    {
        iter.second.Unload();
    }
    mTextures.clear();
}

ShaderProgram* Assets::LoadShaderProgram(const std::string& pVert, const std::string& pFrag, const std::string& pName)
{
    Shader vert;
    vert.Load(pVert, ShaderType::VERTEX);
    Shader frag;
    frag.Load(pFrag, ShaderType::FRAGMENT);

    mShaderPrograms[pName].Compose({ &vert, &frag });
    return &mShaderPrograms[pName];
}

ShaderProgram& Assets::GetShaderProgram(const std::string& pName)
{
    if (!mShaderPrograms.count(pName) != 0)
    {
        Log::Error(LogType::Application, "Shader program " + pName + " does not exist");
    }
    return mShaderPrograms[pName];
}



Texture Assets::LoadTextureFromFile(IRenderer& pRenderer, const std::string& pFileName)
{
    Texture texture;
    texture.Load(pRenderer, pFileName);
    return texture;
}

Mesh Assets::LoadMesh(const std::string& pFileName, const std::string& pName)
{
    mMeshes[pName] = LoadMeshFromFile(pFileName);
    return mMeshes[pName];
}

Mesh& Assets::GetMesh(const std::string& pName)
{
    if (mMeshes.count(pName) != 0)
    {
        return mMeshes[pName];
    }
    else
    {
        Log::Error(LogType::Application, "Mesh" + pName + " does not exist");
    }
}

Mesh Assets::LoadMeshFromFile(const std::string& pFileName)
{
    Mesh loaded;
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warning, errors;
    std::string dir = "Meshes/";
    bool success = tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &errors, +pFileName.c_str());
    if (!success)
    {
        Log::Error(LogType::Application, "Mesh " + pFileName + " does not exist or is not .obj");
        return Mesh();
    }
    else
    {
        Log::Info("Mesh " + pFileName + " successfully loaded");
    }
    std::vector<Vertex> vertices;
    for (int i = 0; i < shapes.size(); i++)
    {
        tinyobj::shape_t& shape = shapes[i];
        tinyobj::mesh_t& mesh = shape.mesh;
        for (int j = 0; j < mesh.indices.size(); j++)
        {
            tinyobj::index_t i = mesh.indices[j];
            Vector3 position = Vector3{
                attributes.vertices[i.vertex_index * 3],
                attributes.vertices[i.vertex_index * 3 + 1],
                attributes.vertices[i.vertex_index * 3 + 2]
            };
            Vector3 normal = Vector3{
                attributes.normals[i.normal_index * 3],
                attributes.normals[i.normal_index * 3 + 1],
                attributes.normals[i.normal_index * 3 + 2]
            };
            Vector2 texCoord = {
                attributes.texcoords[i.texcoord_index * 2],
                attributes.texcoords[i.texcoord_index * 2 + 1],
            };
            // Not gonna care about texCoord right now.
            Vertex vert = { position, normal, texCoord };
            vertices.push_back(vert);
        }

    }
    return Mesh(vertices);
}

