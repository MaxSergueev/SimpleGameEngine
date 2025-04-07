#include "Mesh.h"
Mesh::Mesh() : mVertexArray(nullptr)
{
	mVertexArray = new VertexArray(cubeVertices, 28, cubeIndices, 36);
	mVertexShader.Load("Basic.vert", ShaderType::VERTEX);
	mFragmentShader.Load("Basic.frag", ShaderType::FRAGMENT);
	mShaderProgram.Compose({ &mVertexShader, &mFragmentShader });
	mTextures.emplace_back(&Assets::GetTexture("wall"));
}
void Mesh::Unload()
{
	delete mVertexArray;
	mVertexArray = nullptr;
}

Texture* Mesh::GetTexture(size_t textureIndex) {
	if (textureIndex < mTextures.size()) return mTextures[textureIndex];
	return nullptr;
}

ShaderProgram& Mesh::GetShaderProgram()
{
	return mShaderProgram;
}