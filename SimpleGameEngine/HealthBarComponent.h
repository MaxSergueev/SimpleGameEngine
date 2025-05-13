#pragma once
#include "Component.h"
#include "Vector3.h"
#include <string>

class Actor;
class HealthComponent;
class SpriteComponent;

class HealthBarComponent : public Component
{
public:
    HealthBarComponent(Actor* pOwner, int updateOrder = 200);
    ~HealthBarComponent() override;

    void Update() override;

    // Set the health component to monitor
    void SetHealthComponent(HealthComponent* healthComponent) { mHealthComponent = healthComponent; }

    // Set position of the health bar in screen space
    void SetPosition(const Vector3& position);

    // Set size of the health bar
    void SetSize(const Vector3& size);

    // Set textures for background and foreground
    void SetBackgroundTexture(const std::string& textureName);
    void SetForegroundTexture(const std::string& textureName);

private:
    HealthComponent* mHealthComponent;

    // Actors for the health bar parts
    Actor* mBackgroundActor;
    Actor* mForegroundActor;

    // Sprite components
    SpriteComponent* mBackgroundSprite;
    SpriteComponent* mForegroundSprite;

    // Size and position
    Vector3 mPosition;
    Vector3 mSize;

    // Initial width for scaling calculations
    float mInitialWidth;
};

