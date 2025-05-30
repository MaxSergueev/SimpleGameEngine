#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
#include "BulletPool.h"
class DoomScene : public Scene
{
public:
    Shader* mSimpleVert = new Shader();
    Shader* mSimpleFrag = new Shader();

    Shader* mFloorFrag = new Shader();
    Shader* mFloorVert = new Shader();

    ShaderProgram* sp = new ShaderProgram();

    BulletPool* mBulletPool;

    DoomScene();
    ~DoomScene() override;
    void Start() override;
    void Render() override;
    void Update() override;
    void Close() override;

    void Load() override;

};


