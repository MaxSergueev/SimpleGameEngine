#include "Game.h"
#include "Scenes/Pong.h"
using namespace std;


int main(int argc, char* argv[])
{
	Game myGame("Super game", {new Pong()}, IRenderer::RendererType::SDL);
	myGame.Initialize();
	return 0;
}
