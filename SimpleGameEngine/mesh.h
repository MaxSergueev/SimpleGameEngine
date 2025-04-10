#pragma once
#include "Vector3.h"
#include "VertexArray.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Assets.h"

class VertexArray;

struct Vertex
{
public:
    Vector3 position;
    Vector3 normal;
    Vector2 texCoord;
};

class Mesh
{
public:
    Mesh();
    Mesh(std::vector<Vertex> pVertices);
    ~Mesh();
    float* ToVerticeArray();
    void Unload();
    ShaderProgram& GetShaderProgram();
    void SetShaderProgram(ShaderProgram* pShader);
    Texture* GetTexture(size_t textureIndex);
    VertexArray* GetVertexArray() { return mVertexArray; }

private:
    VertexArray* mVertexArray;
    Shader mVertexShader;
    Shader mFragmentShader;
    ShaderProgram mShaderProgram;
    std::vector<Texture*> mTextures;
    std::vector<Vertex> mVertices;
};

