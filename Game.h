#pragma once

#include<map>
#include<string>
#include<sstream>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"

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
	int type;
	sf::Vector2f pos;

	//Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();
	
	void initPlayer();
	void initEnemies();

public:
	Game();
	virtual ~Game();
	
	//Functions
	void run();
	void updateMousePositions();
	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
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
		if (this->player->getBounds().top < 0.f)
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
	void updateCombat();
	void update();
	
	void renderGUI();
	void renderWorld();
	void render();
};