#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
class BowlingScene : public Scene
{
public:
    Shader* mSimpleVert = new Shader();
    Shader* mSimpleFrag = new Shader();
    ShaderProgram* sp = new ShaderProgram();

    BowlingScene();
    ~BowlingScene() override = default;
    void Start() override;
    void Render() override;
    void Update() override;
    void Close() override;

    void Load() override;

};

