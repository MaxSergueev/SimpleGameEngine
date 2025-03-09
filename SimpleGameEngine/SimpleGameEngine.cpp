#include "Game.h"
#include "Scenes/Pong.h"
#include "GlTestScene.h"
using namespace std;


int main(int argc, char* argv[])
{
	Game myGame("Super game", {new GlTestScene()}, IRenderer::RendererType::OPENGL);
	myGame.Initialize();
	return 0;
}
