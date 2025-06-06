#pragma once
#include "SpriteComponent.h"
using std::vector;

/**
 * @brief Sprite component that supports frame-based animation
 *
 * AnimatedSpriteComponent extends SpriteComponent to provide frame-based
 * animation functionality. It cycles through a sequence of textures at
 * a specified frame rate to create animated sprites.
 */
class AnimatedSpriteComponent : public SpriteComponent
{
private:
    vector<Texture*> mAnimationTextures;    ///< Sequence of textures for animation frames
    float mCurrentFrame;                    ///< Current frame index (can be fractional)
    float mAnimFps;                         ///< Animation playback speed in frames per second

public:
    /**
     * @brief Constructs an animated sprite component
     * @param pOwner The actor that owns this component
     * @param pTexture Vector of textures to use for animation frames
     * @param pDrawOrder Drawing order for sprite rendering (higher values drawn last)
     */
    AnimatedSpriteComponent(Actor* pOwner, const vector<Texture*>& pTexture, int pDrawOrder = 100);

    /**
     * @brief Virtual destructor
     */
    virtual ~AnimatedSpriteComponent();

    AnimatedSpriteComponent() = delete;
    AnimatedSpriteComponent(const AnimatedSpriteComponent&) = delete;
    AnimatedSpriteComponent& operator=(const AnimatedSpriteComponent&) = delete;

    /**
     * @brief Gets the current animation frame rate
     * @return The animation speed in frames per second
     */
    float GetAnimationFps() const { return mAnimFps; }

    /**
     * @brief Sets the textures used for animation frames
     * @param pTextures Vector of texture pointers for each frame
     */
    void SetAnimationTextures(const vector<Texture*>& pTextures);

    /**
     * @brief Sets the animation playback speed
     * @param pFps The desired frame rate in frames per second
     */
    void SetAnimationFps(float pFps);

    /**
     * @brief Updates the animation frame based on elapsed time
     */
    void Update() override;
};



