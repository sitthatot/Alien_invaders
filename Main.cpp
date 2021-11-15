#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include <time.h>
#include "Menu.h"
#include "Highscore.h"
#include "Entername.h"
#include "SFML/Audio.hpp"
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
	selectSound.setVolume(70);

	sf::Music stageMusic;
	stageMusic.openFromFile("Textures/sounds/Jungle.wav");
	stageMusic.setLoop(true);
	stageMusic.setVolume(50);
	

	sf::Music gameOpen;
	gameOpen.openFromFile("Textures/sounds/title.wav");
	gameOpen.setLoop(false);
	gameOpen.setVolume(50);
	gameOpen.play();
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
			stageMusic.play();
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
	return 0;
}