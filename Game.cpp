#include "Game.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include <SFML/Network.hpp>
#include <math.h>
#include <vector>
#include <cstdlib>
using namespace sf;
using namespace std;

Vector2f playerCenter;
Vector2f mousePosWindow;
Vector2f aimDir;
Vector2f aimDirNorm;

void Game::updateMousePositions()
{
	//return void, updates the mouse positions: *Mouse position relative to window(Vector2i)
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}
//Private functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1078, 850), "Invaders", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/AGoblinAppears-o2aV.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	//Init point text
	this->pointText.setPosition(850.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	//Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/background2.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
	this->player->setPosition(500.f, 350.f);
}

void Game::initEnemies()
{//Spawn enemy
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

//Con/Des
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSystems();

	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
		break;
	}

	//Delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
		break;
	}

	//Delete enemies
	for (auto* i : this->enemies)
	{
		delete i;
		break;
	}
}

//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();

		if (this->player->getHp() > 0)
			this->update();

		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{
	//Move player
	this->player->move(0.f, 0.f, mousePosView);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f, mousePosView);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f, mousePosView);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f, mousePosView);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f, mousePosView);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(
				this->textures["BULLET"],
				this->player->getPos().x - 30,
				this->player->getPos().y - 30,
				1.f,//sf::Mouse::getPosition(*this->window).x,//dirx
				1.f,//sf::Mouse::getPosition(*this->window).y,//dir_y
				5.f,//movement speed
				this->player->getAngle()
			)
		);
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Points: " << this->points;

	this->pointText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{

}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			break;
		}
		//Enemy player collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			break;
		}

		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();

	this->updateGUI();

	this->updateWorld();

	this->mousePosView = sf::Vector2f(sf::Mouse::getPosition(*window));

	std::cout << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << "\n";
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();

	//Draw world
	this->renderWorld();

	//Draw all the stuffs
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0)
		this->window->draw(this->gameOverText);

	this->window->display();
}