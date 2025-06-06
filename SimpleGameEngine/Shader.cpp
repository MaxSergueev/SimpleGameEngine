#include "Shader.h"
#include "Log.h"
#include <glew.h>

const std::string Shader::SHADER_PATH = "Resources/Shaders/";

Shader::Shader() : mId(0), mCode(""), mType(VERTEX) {}

Shader::Shader(int pId, std::string pCode, ShaderType pType) :mId(pId), mCode(pCode), mType(pType)
{
}

Shader::~Shader()
{
}

std::string& Shader::GetCode()
{
    return mCode;
}

void Shader::Load(std::string pFileName, ShaderType pShaderType)
{
    mType = pShaderType;
    std::ifstream myFile;
    myFile.open(SHADER_PATH + pFileName);
    if (myFile.fail()) {
        Log::Error(LogType::Video, "Error - failed to open " + pFileName);
    }
    std::string fileText = "";
    std::string line = "";
    while (getline(myFile, line)) {
        fileText += line + '\n';
    }

    myFile.close();
    mCode = fileText;

    switch (mType)
    {
    case VERTEX: {
        mId = glCreateShader(GL_VERTEX_SHADER);
        break;
    }
    case FRAGMENT: {
        mId = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    }
    case TESSELLATION_CONTROL: {
        mId = glCreateShader(GL_TESS_CONTROL_SHADER);
        break;
    }
    case TESSELLATION_EVALUATION: {
        mId = glCreateShader(GL_TESS_EVALUATION_SHADER);
        break;
    }
    case GEOMETRY: {
        mId = glCreateShader(GL_GEOMETRY_SHADER);
        break;
    }
    default:
    {
        Log::Error(LogType::Render, "This shader type has not yet been implemented.");
        mId = glCreateShader(GL_VERTEX_SHADER);
        break;
    }
    }

    const char* source = mCode.c_str();
    glShaderSource(mId, 1, &source, NULL);
    glCompileShader(mId);

    GLint success;
    glGetShaderiv(mId, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(mId, 1024, NULL, infoLog);
        Log::Error(LogType::Render, "Shader compilation failed for " + pFileName + ": " + std::string(infoLog));
    }
}
