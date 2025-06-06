#include "Game.h"
#include "Scenes/Pong.h"
#include "GlTestScene.h"
#include "BowlingScene.h"
#include "DoomScene.h"
#include "PlanetScene.h"
using namespace std;


int main(int argc, char* argv[])
{
	//Game myGame("Super game", {new GlTestScene()}, IRenderer::RendererType::OPENGL);
	//Game myGame("Super game", { new BowlingScene() }, IRenderer::RendererType::OPENGL);
	Game myGame("Super game", { new DoomScene() }, IRenderer::RendererType::OPENGL);
	//Game myGame("Super game", { new PlanetScene() }, IRenderer::RendererType::OPENGL);
	myGame.Initialize();
	return 0;
}
