#include "RendererGL.h"
#include <glew.h>
#include "Log.h"
#include <SDL_image.h>
#include "SpriteComponent.h"
#include "MeshComponent.h"

RendererGl::RendererGl() :
	mWindow(nullptr),
	mSpriteVao(nullptr),
	mContext(nullptr),
	mSpriteShaderProgram(nullptr),
	mSpriteViewProj(Matrix4Row::CreateSimpleViewProj(800.0f, 600.0f)),
	mView(Matrix4Row::CreateLookAt(Vector3(0, 0, 5), Vector3::unitX, Vector3::unitZ)),
	mProjection(Matrix4Row::CreatePerspectiveFOV(70.0f, 800.0f, 600.0f, 0.01f, 10000.0f))
{
}

bool RendererGl::Initialize(Window& rWindow)
{
	mWindow = &rWindow;

	// Setting OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// 8 bits color buffer
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	// Set up projection matrix for sprites
	mSpriteViewProj = Matrix4Row::CreatePerspectiveFOV(
		70.0f,  // Field of view
		static_cast<float>(mWindow->GetDimensions().x),  // Window Width
		static_cast<float>(mWindow->GetDimensions().y),  // Window Height
		0.1f,  // Near plane
		10000.0f  // Far plane
	);

	// Set up view and projection matrices for 3D rendering
	mView = Matrix4Row::CreateLookAt(
		Vector3(0.0f, 0.0f, 5.0f),  // Camera position
		Vector3(1.0f, 0.0f, 0.0f),   // Target position
		Vector3(0.0f, 0.0f, 1.0f)    // Up vector
	);

	mProjection = Matrix4Row::CreatePerspectiveFOV(
		90.0f,  // Field of view
		static_cast<float>(mWindow->GetDimensions().x),  // Window Width
		static_cast<float>(mWindow->GetDimensions().y),  // Window Height
		0.1f,  // Near plane
		10000.0f  // Far plane
	);

	mContext = SDL_GL_CreateContext(mWindow->GetSdlWindow());
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		Log::Error(LogType::Video, "Failed to initialize GLEW");
		return false;
	}
	glGetError();

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		Log::Error(LogType::Video, "Failed to initialize SDL_Image");
	}
	mSpriteVao = new VertexArray(spriteVertices, 4);
	return true;
}

RendererGl::~RendererGl()
{
	delete mSpriteVao;
}
void RendererGl::BeginDraw()
{
	glClearColor(0.45f, 0.45f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (mSpriteShaderProgram != nullptr) mSpriteShaderProgram->Use();
	mSpriteShaderProgram->setMatrix4Row("uViewProj", mSpriteViewProj);
	mSpriteVao->SetActive();
}

void RendererGl::Draw()
{
	DrawMeshes();
    DrawSprites();
}

void RendererGl::DrawSprite(Actor& pActor, const Texture& pTex, Rectangle pSourceRect, Vector2 pOrigin,
	Flip pFlip) const
{
	mSpriteShaderProgram->Use();
	pActor.GetTransform().ComputeWorldTransform();
	Matrix4Row scaleMat = Matrix4Row::CreateScale(
		pTex.GetWidth(),
		pTex.GetHeight(),
		0.0f);
	Matrix4Row world = scaleMat * pActor.GetTransform().GetWorldTransform();
	mSpriteShaderProgram->setMatrix4Row("uWorldTransform", world);
	pTex.SetActive();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}



void RendererGl::DrawSprites()
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (mSpriteShaderProgram != nullptr) mSpriteShaderProgram->Use();
	mSpriteShaderProgram->setMatrix4Row("uViewProj", mSpriteViewProj);
	mSpriteVao->SetActive();

	for (SpriteComponent* sprite : mSprites)
	{
		sprite->Draw(*this);
	}
}

void RendererGl::EndDraw()
{
	SDL_GL_SwapWindow(mWindow->GetSdlWindow());
}

void RendererGl::AddSprite(SpriteComponent* pSprite)
{
	int spriteDrawOrder = pSprite->GetDrawOrder();
	std::vector<SpriteComponent*>::iterator sc;
	for (sc = mSprites.begin(); sc != mSprites.end(); ++sc)
	{
		if (spriteDrawOrder < (*sc)->GetDrawOrder()) break;
	}
	mSprites.insert(sc, pSprite);
}

void RendererGl::RemoveSprite(SpriteComponent* pSprite)
{
	std::vector<SpriteComponent*>::iterator sc;
	sc = std::find(mSprites.begin(), mSprites.end(), pSprite);
	mSprites.erase(sc);
}

void RendererGl::Close()
{
	SDL_GL_DeleteContext(mContext);
	delete mSpriteVao;
}

IRenderer::RendererType RendererGl::GetType()
{
	return RendererType::OPENGL;
}

void RendererGl::SetSpriteShaderProgram(ShaderProgram* shaderProgram)
{
	mSpriteShaderProgram = shaderProgram;
}

void RendererGl::AddMesh(MeshComponent* pMesh)
{
	mMeshes.push_back(pMesh);
}

void RendererGl::RemoveMesh(MeshComponent* pMesh)
{
	auto iter = std::find(mMeshes.begin(), mMeshes.end(), pMesh);
	if (iter != mMeshes.end())
	{
		mMeshes.erase(iter);
	}
}

void RendererGl::DrawMeshes()
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	for (MeshComponent* m : mMeshes)
	{
		m->Draw(mView * mProjection);
	}
}

void RendererGl::SetViewMatrix(Matrix4Row view)
{
	mView = view;
}

