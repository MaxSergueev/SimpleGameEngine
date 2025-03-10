#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"


class RendererGl : public IRenderer
{
private:
	Window* mWindow;
	VertexArray* mVao;
	ShaderProgram* mShaderProgram;
	SDL_GLContext mContext;
	std::vector<SpriteComponent*> mSprites;
	Matrix4Row mViewProj; //////////////////////// What is this supposed to be
public:
	RendererGl();
	virtual ~RendererGl();
	RendererGl(const RendererGl&) = delete;
	RendererGl& operator=(const RendererGl&) = delete;

	bool Initialize(Window& rWindow) override;
	void BeginDraw() override;
	void Draw() override;
	void DrawSprite(Actor& pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin, Flip pFlip = Flip::None) const override;
	void EndDraw() override;
	void Close() override;
	RendererType GetType() override;

	// Inherited via IRenderer
	void DrawSprites() override;
	void AddSprite(SpriteComponent* pSprite);
	void RemoveSprite(SpriteComponent* pSprite);
};


