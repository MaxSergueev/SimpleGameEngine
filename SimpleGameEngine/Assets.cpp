#include "Assets.h"
#include <sstream>

#include "Log.h"

std::map<std::string, Texture> Assets::mTextures = {};
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
