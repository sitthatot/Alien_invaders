#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include<time.h>
#include "Menu.h"
//using namespace sf;

int main()
{
	
	sf::RenderWindow window(sf::VideoMode(1078, 850), "Invaders");
	Menu menu(window.getSize().x,window.getSize().y);
	sf::Texture texture;
	if (!texture.loadFromFile("Textures/menu_bg.JPG")) {

	}
	sf::Sprite background;
	background.setTexture(texture);
	srand(time(nullptr));
	Game game;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					menu.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						std::cout << "Play";
						//go to state
						
						
						game.run();
						break;
					case 1:
						std::cout << "leader";
						//go to state
						break;
					case 2:
						window.close();
						break;
					}
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();
		window.draw(background);
		menu.draw(window);
		window.display();
	}
	
		
		//Init srand
	//srand(time(nullptr));
		//Init Game engine
	//Game game;
	//game.run();

		//End of application
	return 0;
}