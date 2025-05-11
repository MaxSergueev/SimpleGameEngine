#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
class DoomScene : public Scene
{
public:
    Shader* mSimpleVert = new Shader();
    Shader* mSimpleFrag = new Shader();

    Shader* mFloorFrag = new Shader();
    Shader* mFloorVert = new Shader();

    ShaderProgram* sp = new ShaderProgram();

    DoomScene();
    ~DoomScene() override = default;
    void Start() override;
    void Render() override;
    void Update() override;
    void Close() override;

    void Load() override;

};


