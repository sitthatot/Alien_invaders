#include <iostream>
#include "Game.h"
#include<time.h>

//using namespace sf;

int main()
{

	//Init srand
	srand(time((0)));

	//Init Game engine
	Game game;
	game.run();

	//End of application
	return 0;
}