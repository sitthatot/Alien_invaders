#include <iostream>
#include "Game.h"

//using namespace sf;

int main()
{

	//Init srand
	std::srand(static_cast<unsigned>(time(NULL)));

	//Init Game engine
	Game game;
	game.run();

	//End of application
	return 0;
}