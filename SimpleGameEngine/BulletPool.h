#pragma once
#include <vector>
#include "Bullet.h"
#include "Vector3.h"

class Scene;

class BulletPool
{
public:
    BulletPool(Scene* scene, int poolSize = 50);
    ~BulletPool();

    // Fire a bullet
    bool FireBullet(const Vector3& startPos, const Vector3& direction, Actor* shooter, float speed = 500.0f);

    // Update all active bullets
    void Update();

    // Get number of active bullets
    int GetActiveBulletCount() const;

private:
    std::vector<Bullet*> mBullets;
    Scene* mScene;
    int mPoolSize;
    int mNextBulletIndex;

    Bullet* GetAvailableBullet();
};


