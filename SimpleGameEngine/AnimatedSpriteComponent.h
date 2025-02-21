#pragma once
#include "SpriteComponent.h"
using std::vector;

class AnimatedSpriteComponent : public SpriteComponent
{
private:
	vector<Texture*> mAnimationTextures;
	float mCurrentFrame;
	float mAnimFps;
public:
	AnimatedSpriteComponent(Actor* pOwner, const vector<Texture*>& pTexture, int pDrawOrder = 100);
	virtual ~AnimatedSpriteComponent();
	AnimatedSpriteComponent() = delete;
	AnimatedSpriteComponent(const AnimatedSpriteComponent&) = delete;
	AnimatedSpriteComponent& operator=(const AnimatedSpriteComponent&) = delete;

	float GetAnimationFps() const { return mAnimFps; }
	void SetAnimationTextures(const vector<Texture*>& pTextures);
	void SetAnimationFps(float pFps);

	void Update() override;

};


