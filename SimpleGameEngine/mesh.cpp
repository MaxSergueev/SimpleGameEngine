#include "Mesh.h"
#include "VertexArray.h"

Mesh::Mesh() : mVertexArray(nullptr)
{
    mVertexShader.Load("Basic.vert", ShaderType::VERTEX);
    mFragmentShader.Load("Basic.frag", ShaderType::FRAGMENT);
    mShaderProgram.Compose({ &mVertexShader, &mFragmentShader });
}

Mesh::Mesh(std::vector<Vertex> pVertices) : mVertices(std::move(pVertices)), mVertexArray(nullptr)
{
    float* verticeInfo = ToVerticeArray();
    mVertexArray = new VertexArray(verticeInfo, mVertices.size());
    delete[] verticeInfo;
    mVertexShader.Load("Basic.vert", ShaderType::VERTEX);
    mFragmentShader.Load("Basic.frag", ShaderType::FRAGMENT);
    mShaderProgram.Compose({ &mVertexShader, &mFragmentShader });
    mTextures.emplace_back(&Assets::GetTexture("wall"));
}

Mesh::~Mesh() = default;

void Mesh::Unload()
{
    delete mVertexArray;
    mVertexArray = nullptr;
}

Texture* Mesh::GetTexture(size_t textureIndex)
{
    if (textureIndex < mTextures.size()) return mTextures[textureIndex];
    return nullptr;
}

void Mesh::SetTexture(Texture* texture, size_t index)
{
    if (index >= mTextures.size()) {
        mTextures.resize(index + 1, nullptr);
    }
    mTextures[index] = texture;
}

ShaderProgram& Mesh::GetShaderProgram()
{
    return mShaderProgram;
}

void Mesh::SetShaderProgram(ShaderProgram* pShader)
{
    mShaderProgram = *pShader;
}

float* Mesh::ToVerticeArray()
{
    float* array = new float[mVertices.size() * 8];
    int counter = 0;
    for (int i = 0; i < mVertices.size(); i++)
    {
        array[counter + 0] = mVertices[i].position.x;
        array[counter + 1] = mVertices[i].position.y;
        array[counter + 2] = mVertices[i].position.z;
        array[counter + 3] = mVertices[i].normal.x;
        array[counter + 4] = mVertices[i].normal.y;
        array[counter + 5] = mVertices[i].normal.z;
        array[counter + 6] = mVertices[i].texCoord.x;
        array[counter + 7] = mVertices[i].texCoord.y;
        counter += 8;
    }
    return array;
}
