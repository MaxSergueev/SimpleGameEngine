#include "HealthBarComponent.h"
#include "Actor.h"
#include "Scene.h"
#include "SpriteComponent.h"
#include "HealthComponent.h"
#include "Assets.h"

HealthBarComponent::HealthBarComponent(Actor* pOwner, int updateOrder)
    : Component(pOwner, updateOrder),
    mHealthComponent(nullptr),
    mBackgroundActor(nullptr),
    mForegroundActor(nullptr),
    mBackgroundSprite(nullptr),
    mForegroundSprite(nullptr),
    mPosition(250, 50, 1000),
    mSize(200, 20, 1),
    mInitialWidth(200)
{
    mBackgroundActor = new Actor();
    mOwner->GetScene().AddActor(mBackgroundActor);
    mBackgroundActor->SetPosition(mPosition);
    mBackgroundActor->SetScale(mSize);

    mForegroundActor = new Actor();
    mOwner->GetScene().AddActor(mForegroundActor);
    mForegroundActor->SetPosition(Vector3(mPosition.x, mPosition.y, mPosition.z));
    mForegroundActor->SetScale(mSize);

    SetBackgroundTexture("purple");
    SetForegroundTexture("yellow");
}

HealthBarComponent::~HealthBarComponent()
{
    if (mBackgroundActor) mBackgroundActor->Destroy();
    if (mForegroundActor) mForegroundActor->Destroy();
}

void HealthBarComponent::Update()
{
    if (!mHealthComponent || !mForegroundActor) return;

    float healthPercent = mHealthComponent->GetHealthPercentage();

    Vector3 scale = mSize;
    scale.x = mInitialWidth * healthPercent;

    mForegroundActor->SetScale(scale);

    float xOffset = (mInitialWidth - scale.x) / 2.0f;
    Vector3 newPosition = mPosition;
    newPosition.x -= xOffset * 1030; // Scaling factor for 3D space positioning

    mForegroundActor->SetPosition(Vector3(newPosition.x, newPosition.y, mPosition.z - 1));
}

void HealthBarComponent::SetPosition(const Vector3& position)
{
    mPosition = position;

    mBackgroundActor->SetPosition(mPosition);
    mForegroundActor->SetPosition(Vector3(mPosition.x, mPosition.y, mPosition.z - 1));
}

void HealthBarComponent::SetSize(const Vector3& size)
{
    mSize = size;
    mInitialWidth = size.x;

    mBackgroundActor->SetScale(mSize);
    mForegroundActor->SetScale(mSize);
}

void HealthBarComponent::SetBackgroundTexture(const std::string& textureName)
{
    mBackgroundSprite = new SpriteComponent(mBackgroundActor, Assets::GetTexture(textureName));
}

void HealthBarComponent::SetForegroundTexture(const std::string& textureName)
{
    mForegroundSprite = new SpriteComponent(mForegroundActor, Assets::GetTexture(textureName));
}