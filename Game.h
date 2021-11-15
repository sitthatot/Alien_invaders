#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include <SFML/Network.hpp>
#include <math.h>
#include <vector>
#include <cstdlib>
#include<map>

#include<string>
#include<sstream>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include "Item.h"
#include "Menu.h"
#include "Entername.h"


class Game
{
private:

	//Window
	sf::RenderWindow* window;
	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;
	sf::Text healthText;
	sf::Text gameOverText;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Systems
	unsigned health;
	unsigned points;

	//Player
	Player* player;

	//Item
	std::vector<Item*> items;
	float itemSpawnTimer;
	float itemSpawnTimerMax;
	float setScale[2];
	int randomItem;
	int type_item;
	sf::Texture itemTexture[2];
	sf::Sprite itemSprite[2];

	//Score
	FILE* fq;
	char temp[255];
	int score[6];
	std::string name[6];
	std::vector <std::pair<int, std::string>> userScore;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	sf::Texture enemysprite[2];
	sf::Texture itemsprite[2];
	int type;
	sf::Vector2f pos;
	Entername* entername;
	//Sounds
	sf::SoundBuffer itemSoundBuffer;
	sf::Sound itemSound;
	sf::SoundBuffer playerCollideSoundBuffer;
	sf::Sound playerCollideSound;
	sf::SoundBuffer gunSoundBuffer;
	sf::Sound gunSound;
	//Con Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();
	void initPlayer();
	void initItem();
	void initEnemies();
public:
	Game(sf::RenderWindow *window, Entername *entername);
	virtual ~Game();

	//Functions
	void run();
	void updateMousePositions();
	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateCollision()
	{
		//Left world collision
		if (this->player->getBounds().left < 0.f)
		{
			this->player->setPosition(0.f, this->player->getBounds().top);
		}
		//Right world collison
		else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
		{
			this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
		}

		//Top world collision
		if (this->player->getBounds().top< 0.f)
		{
			this->player->setPosition(this->player->getBounds().left, 0.f);
		}
		//Bottom world collision
		else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
		{
			this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
		}
	}
	void updateBullets();
	void updateEnemies();
	void updateItem();
	void updateCombat();
	void update();
	void renderGUI();
	void renderWorld();
	void render();
	void updateHigh(std::string name, unsigned int score);
};