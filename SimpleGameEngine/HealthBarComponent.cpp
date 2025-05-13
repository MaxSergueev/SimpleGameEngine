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
    // Create background actor
    mBackgroundActor = new Actor();
    mOwner->GetScene().AddActor(mBackgroundActor);
    mBackgroundActor->SetPosition(mPosition);
    mBackgroundActor->SetScale(mSize);

    // Create foreground actor
    mForegroundActor = new Actor();
    mOwner->GetScene().AddActor(mForegroundActor);
    mForegroundActor->SetPosition(Vector3(mPosition.x, mPosition.y, mPosition.z));
    mForegroundActor->SetScale(mSize);

    // Default textures
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

    // Update health bar width based on health percentage
    float healthPercent = mHealthComponent->GetHealthPercentage();

    // Calculate new scale for foreground
    Vector3 scale = mSize;
    scale.x = mInitialWidth * healthPercent;

    // Update foreground scale
    mForegroundActor->SetScale(scale);

    // Calculate new position to anchor the health bar to the left
    float xOffset = (mInitialWidth - scale.x) / 2.0f;
    Vector3 newPosition = mPosition;
	newPosition.x -= xOffset * 1030; // !!!!!!!!! Sprite is in 3D space so the value 1030 is there since I put the sprite "far" from the camera

    // Update foreground position
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
    // Add new sprite component
    mBackgroundSprite = new SpriteComponent(mBackgroundActor, Assets::GetTexture(textureName));
}

void HealthBarComponent::SetForegroundTexture(const std::string& textureName)
{
    // Add new sprite component
    mForegroundSprite = new SpriteComponent(mForegroundActor, Assets::GetTexture(textureName));
}






