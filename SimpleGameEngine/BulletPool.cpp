#include "BulletPool.h"
#include "Scene.h"
#include "Log.h"

BulletPool::BulletPool(Scene* scene, int poolSize)
    : mScene(scene), mPoolSize(poolSize), mNextBulletIndex(0)
{
    mBullets.reserve(poolSize);

    for (int i = 0; i < poolSize; i++)
    {
        Bullet* bullet = new Bullet();
        mScene->AddActor(bullet);
        bullet->Reset();
        mBullets.push_back(bullet);
    }

    Log::Info("BulletPool created with " + std::to_string(poolSize) + " bullets");
}

BulletPool::~BulletPool()
{
}

bool BulletPool::FireBullet(const Vector3& startPos, const Vector3& direction, Actor* shooter, float speed)
{
    Bullet* bullet = GetAvailableBullet();
    if (bullet)
    {
        bullet->Initialize(startPos, direction, shooter, speed);
        return true;
    }

    Log::Error(LogType::Error, "No available bullets in pool!");
    return false;
}

void BulletPool::Update()
{

}

int BulletPool::GetActiveBulletCount() const
{
    int count = 0;
    for (const Bullet* bullet : mBullets)
    {
        if (bullet->IsActive())
        {
            count++;
        }
    }
    return count;
}

Bullet* BulletPool::GetAvailableBullet()
{
    for (int i = 0; i < mPoolSize; i++)
    {
        int index = (mNextBulletIndex + i) % mPoolSize;
        if (!mBullets[index]->IsActive())
        {
            mNextBulletIndex = (index + 1) % mPoolSize;
            return mBullets[index];
        }
    }

    return nullptr;
}
