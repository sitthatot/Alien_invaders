#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include <time.h>
#include "Menu.h"
#include "Highscore.h"
#include "Entername.h"
#include <vector>
//using namespace sf;

int main()
{
	
	int state = 0;
	sf::RenderWindow window(sf::VideoMode(1078, 850), "Invaders");
	Menu menu(window.getSize().x,window.getSize().y);
	sf::Texture texture;
	sf::SoundBuffer selectSoundBuffer;
	sf::Sound selectSound;
	selectSoundBuffer.loadFromFile("Textures/sounds/select.wav");
	selectSound.setBuffer(selectSoundBuffer);
	if (!texture.loadFromFile("Textures/menu_bg.JPG")) {

	}
	sf::Sprite background;
	background.setTexture(texture);
	srand(time(nullptr));
	Highscore highscore(&window);
	Entername entername(&window);
	Game game(&window, &entername);
	std::vector<sf::Event> textEnter;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::TextEntered:
				if (state == 3) {
					textEnter.push_back(event);
				}
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					selectSound.play();
					menu.MoveUp();
					break;

				case sf::Keyboard::Down:
					selectSound.play();
					menu.MoveDown();
					break;
				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						std::cout << "Play";
						//go to state
						selectSound.play();
						if (state == 3) {
							state = 1;
							break;
						}
						state = 3;
						
						
						break;
					case 1:
						std::cout << "leader";
						selectSound.play();
						state = 2;
						//go to state
						//highscore.render();
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
		switch (state)
		{
		case 0:
			window.clear();
			window.draw(background);
			menu.draw(window);
			window.display();
			break;
		case 1:
			selectSound.play();
			game.run();
			break;
		case 2:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				std::cout << "esc";
				state = 0;
				break;
			default:highscore.render();
				break;
			}
			//highscore.render();
			break;
		case 3:
			entername.enterName(textEnter);
			textEnter.clear();
			entername.render();
			break;
		}

		
	}
	
		
		//Init srand
	//srand(time(nullptr));
		//Init Game engine
	//Game game;
	//game.run();

		//End of application
	return 0;
}