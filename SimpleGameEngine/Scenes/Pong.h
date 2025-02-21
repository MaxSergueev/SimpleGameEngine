#pragma once
#include "../Scene.h"

class Pong: public Scene
{
public:
    Pong();
    ~Pong() override = default;
    void Start() override;
    void Render() override;
    void Update() override;
    void Close() override;
    
    void Load() override;

    Vector2 pos;
};
