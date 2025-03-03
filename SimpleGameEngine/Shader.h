#pragma once
#include <string>
#include <fstream>

enum ShaderType {
	VERTEX,
	FRAGMENT,
};

class Shader
{
protected:
	std::string mCode;
	unsigned int mId;
	ShaderType mType;
	const char* mSource;
public:
	//Feel free to change the shader pat if needed
	static const std::string SHADER_PATH;

	Shader();
	Shader(int pId, std::string pFile, ShaderType pShaderType);
	~Shader();

	int GetID() const { return mId; }
	void Load(std::string pFileName, ShaderType pShaderType);

	std::string& GetCode();

};
