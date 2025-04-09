#pragma once
#include "IRenderer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"


class RendererGl : public IRenderer
{
private:
	Window* mWindow;
	VertexArray* mSpriteVao;
	ShaderProgram* mSpriteShaderProgram;
	Matrix4Row mSpriteViewProj;
	Matrix4Row mView;
	Matrix4Row mProjection;
	SDL_GLContext mContext;
	std::vector<SpriteComponent*> mSprites;
	std::vector<MeshComponent*> mMeshes;
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

	void SetSpriteShaderProgram(ShaderProgram* shaderProgram);

	// Inherited via IRenderer
	void DrawSprites() override;
	void AddSprite(SpriteComponent* pSprite);
	void RemoveSprite(SpriteComponent* pSprite);

	void AddMesh(MeshComponent* pMesh) override;
	void RemoveMesh(MeshComponent* pMesh) override;
	void DrawMeshes() override;

	void SetViewMatrix(Matrix4Row view) override;
};


