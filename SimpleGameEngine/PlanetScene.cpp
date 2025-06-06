#include "PlanetScene.h"
#include "Assets.h"
#include "MeshComponent.h"
#include "Actor.h"
#include "Camera.h"
#include "FPSController.h"
#include "Log.h"
#include "Time.h"

Actor* planetActor;
Camera* planetCamera;

PlanetScene::PlanetScene() : mPlanetActor(nullptr), mCurrentTime(0.0f)
{
}

void PlanetScene::Start()
{
}

void PlanetScene::Render()
{
}

void PlanetScene::Update()
{
    UpdateAllActors();

    // Update time counter
     mCurrentTime += Time::deltaTime;

    // Update time uniform for planet rotation
     if (mPlanetShaderProgram) {
        mPlanetShaderProgram->Use();
        mPlanetShaderProgram->setFloat("uTime", mCurrentTime);

        mPlanetShaderProgram->setTessellationLevels(10.0f, 10.0f);
        mPlanetShaderProgram->setFloat("uDisplacementStrength", 0.15f);
     }
}

void PlanetScene::Close()
{
}

void PlanetScene::Load()
{

	// Load sprite shader
    mSimpleFrag->Load("Sprite.frag", FRAGMENT);
    mSimpleVert->Load("Transform.vert", VERTEX);

    sp->Compose({ mSimpleFrag, mSimpleVert });
    mRenderer->SetSpriteShaderProgram(sp);

    // Load planet shaders
    mPlanetVert->Load("Planet.vert", VERTEX);
    mPlanetTessControl->Load("Planet.tesc", TESSELLATION_CONTROL);
    mPlanetTessEval->Load("Planet.tese", TESSELLATION_EVALUATION);
    mPlanetGeometry->Load("Planet.geom", GEOMETRY);
    mPlanetFrag->Load("Planet.frag", FRAGMENT);

    // Compose the complete shader program
    mPlanetShaderProgram->Compose({
        mPlanetVert,
        mPlanetTessControl,
        mPlanetTessEval,
        mPlanetGeometry,
        mPlanetFrag
        });

    Assets::LoadMesh("Resources/Meshes/sphere.obj", "planetSphere");

    // Load noise texture for displacement
    Assets::LoadTexture(*mRenderer, "Resources/noise.png", "noiseTexture");
    Assets::LoadTexture(*mRenderer, "Resources/purple.png", "skyTexture");

    // Create planet actor
    mPlanetActor = new Actor();
    AddActor(mPlanetActor);
    mPlanetActor->SetPosition(Vector3(0, 0, 0));
    mPlanetActor->SetRotation(Vector3(0, 0, 0));
    mPlanetActor->SetScale(Vector3(50, 50, 50));


    // Add mesh component with planet shader
    MeshComponent* planetMesh = new MeshComponent(mPlanetActor);
    planetMesh->SetMesh(Assets::GetMesh("planetSphere"));
    planetMesh->GetMesh()->SetTexture(&Assets::GetTexture("noiseTexture"));
    planetMesh->GetMesh()->SetShaderProgram(mPlanetShaderProgram);

    // Create camera for viewing the planet
    planetCamera = new Camera();
    AddActor(planetCamera);
    planetCamera->SetPosition(Vector3(0, 0, 10));

    // Add FPS controller for camera movement
    FPSController* cameraController = new FPSController(planetCamera);
    cameraController->OnStart();
}

