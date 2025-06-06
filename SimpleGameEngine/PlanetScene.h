#pragma once
#include "Scene.h"
#include "ShaderProgram.h"

class Actor;

class PlanetScene : public Scene
{
public:
    Shader* mSimpleFrag = new Shader();
    Shader* mSimpleVert = new Shader();

    ShaderProgram* sp = new ShaderProgram();

    Shader* mPlanetVert = new Shader();
    Shader* mPlanetTessControl = new Shader();
    Shader* mPlanetTessEval = new Shader();
    Shader* mPlanetGeometry = new Shader();
    Shader* mPlanetFrag = new Shader();

    ShaderProgram* mPlanetShaderProgram = new ShaderProgram();

    PlanetScene();
    ~PlanetScene() override = default;
    void Start() override;
    void Render() override;
    void Update() override;
    void Close() override;
    void Load() override;

private:
    Actor* mPlanetActor;
    float mCurrentTime;
};

