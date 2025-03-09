#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
class GlTestScene : public Scene
{
public:
    Shader* mSimpleVert = new Shader();
    Shader* mSimpleFrag = new Shader();
	ShaderProgram* sp = new ShaderProgram();

    GlTestScene();
    ~GlTestScene() override = default;
    void Start() override;
    void Render() override;
    void Update() override;
    void Close() override;

    void Load() override;

};

