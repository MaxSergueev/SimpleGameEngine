#pragma once
#include "Vector3.h"
#include "VertexArray.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Assets.h"

class Mesh
{
public:
    Mesh();
    void Unload();
    ShaderProgram& GetShaderProgram();
    Texture* GetTexture(size_t textureIndex);
    VertexArray* GetVertexArray() { return mVertexArray; }

private:
    VertexArray* mVertexArray;
    Shader mVertexShader;
    Shader mFragmentShader;
    ShaderProgram mShaderProgram;
    std::vector<Texture*> mTextures;

    static const float cubeVertices[];
    static const unsigned int cubeIndices[];
};

