#include "FirstPersonActor.h"
#include "FPSController.h"
#include "Scene.h"

FirstPersonActor::FirstPersonActor(Scene* scene)
    : Camera()
{
    scene->AddActor(this);

    FPSController* controller = new FPSController(this);
    controller->OnStart();
}