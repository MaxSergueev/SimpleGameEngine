#pragma once
#include "Vector3.h"
#include "VertexArray.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Assets.h"

constexpr float cubeVertices[] = {
   -0.5, -0.5, -0.5, 0, 0,
   0.5, -0.5, -0.5, 1, 0,
   -0.5, 0.5, -0.5, 0, -1,
   0.5, 0.5, -0.5, 1, -1,
   -0.5, 0.5, 0.5, 0, -1,
   0.5, 0.5, 0.5, 1, -1,
   -0.5, -0.5, 0.5, 0, 0,
   0.5, -0.5, 0.5, 1, 0,
   -0.5, 0.5, -0.5, 0, -1,
   0.5, -0.5, -0.5, 1, 0,
   -0.5, 0.5, -0.5, 0, -1,
   0.5, 0.5, -0.5, 1, -1,
   -0.5, 0.5, 0.5, 0, -1,
   -0.5, 0.5, 0.5, 0, -1,
   0.5, 0.5, 0.5, 1, -1,
   -0.5, -0.5, 0.5, 0, 0,
   -0.5, -0.5, 0.5, 0, 0,
   0.5, -0.5, 0.5, 1, 0,
   -0.5, -0.5, -0.5, 0, 0,
   0.5, -0.5, -0.5, 1, 0,
   0.5, -0.5, -0.5, 1, 0,
   0.5, -0.5, 0.5, 1, 0,
   0.5, 0.5, -0.5, 1, -1,
   0.5, 0.5, 0.5, 1, -1,
   -0.5, -0.5, 0.5, 0, 0,
   -0.5, -0.5, -0.5, 0, 0,
   -0.5, 0.5, 0.5, 0, -1,
   -0.5, 0.5, -0.5, 0, -1
};

constexpr unsigned int cubeIndices[] = {
   2, 1, 0,
   3, 9, 8,
   4, 11, 10,
   5, 11, 12,
   6, 14, 13,
   7, 14, 15,
   18, 17, 16,
   19, 17, 18,
   22, 21, 20,
   23, 21, 22,
   26, 25, 24,
   27, 25, 26
};

class Mesh
{
public:
    Mesh();
    void Unload();
    ShaderProgram& GetShaderProgram();
    ShaderProgram& SetShaderProgram(ShaderProgram* pShader);
    Texture* GetTexture(size_t textureIndex);
    VertexArray* GetVertexArray() { return mVertexArray; }

private:
    VertexArray* mVertexArray;
    Shader mVertexShader;
    Shader mFragmentShader;
    ShaderProgram mShaderProgram;
    std::vector<Texture*> mTextures;
};

