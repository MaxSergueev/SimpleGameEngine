#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
class GlTestScene : public Scene
{
public:
    Shader* mSimpleVert;
    Shader* mSimpleFrag;
    ShaderProgram* sp;

    GlTestScene();
    ~GlTestScene() override = default;
    void Start() override;
    void Render() override;
    void Update() override;
    void Close() override;

    void Load() override;

};

