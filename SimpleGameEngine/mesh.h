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

private:
    VertexArray* mVertexArray;
    Shader mVertexShader;
    Shader mFragmentShader;
    ShaderProgram mShaderProgram;
    std::vector<Texture*> mTextures;

    // Vertex and index data for cube
    static const float cubeVertices[];
    static const unsigned int cubeIndices[];
};

