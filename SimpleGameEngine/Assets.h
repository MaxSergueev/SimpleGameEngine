#pragma once
#include <map>
#include <string>
#include "Texture.h"

//SINGLETON CLASS
class Assets
{
public:
    //Storage for future References
    static std::map<std::string, Texture> mTextures;
    
    static Texture LoadTexture(IRenderer& pRenderer, const std::string& pFileName, const std::string& pName);
    static Texture& GetTexture(const std::string& pName);
    static void Clear();

private:
    Assets() = default;
    static Texture LoadTextureFromFile(IRenderer& pRenderer, const std::string& pFileName);
};
