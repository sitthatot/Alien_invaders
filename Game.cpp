#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include "Menu.h"
#include "SFML/Audio.hpp"
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
{//1078, 580
	
	//this->window->setFramerateLimit(144);
	//this->window->setVerticalSyncEnabled(false);
}



void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
	this->enemysprite[0].loadFromFile("Textures/aliena.png");
	this->enemysprite[1].loadFromFile("Textures/roboball.png");
	this->itemTexture[0].loadFromFile("Textures/heart.png");
	this->itemTexture[1].loadFromFile("Textures/shotgun.png");
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
	this->playerHpBar.setSize(sf::Vector2f(150.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}//ค่า HP

void Game::initWorld()//background เกม
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
	this->playerCollideSoundBuffer.loadFromFile("Textures/sounds/enemy-hit.wav");
	this->playerCollideSound.setBuffer(this->playerCollideSoundBuffer);
	this->playerCollideSound.setVolume(40);

	this->gunSoundBuffer.loadFromFile("Textures/sounds/gun.wav");
	this->gunSound.setBuffer(gunSoundBuffer);
	this->gunSound.setVolume(60);
}

void Game::initItem()
{
	//Spawn Item
	this->itemSpawnTimerMax = 500.f;
	this->itemSpawnTimer = this->spawnTimerMax;
}

void Game::initEnemies()
{//Spawn enemy

	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

//Con/Des
Game::Game(sf::RenderWindow* window, Entername* entername)
{
	this->window = window;
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSystems();
	this->initPlayer();
	this->initItem();
	this->initEnemies();
	this->entername = entername;
	
}

Game::~Game()
{
	//delete this->window;
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

	for (auto* i : this->items)
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->player->getBounds().left >= 0.f)
		this->player->move(-1.f, 0.f, mousePosView);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->player->getBounds().left + this->player->getBounds().width < this->window->getSize().x)
		this->player->move(1.f, 0.f, mousePosView);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->player->getBounds().top >= 0.f)
		this->player->move(0.f, -1.f, mousePosView);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->player->getBounds().top + this->player->getBounds().height < this->window->getSize().y)
		this->player->move(0.f, 1.f, mousePosView);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->gunSound.play();
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
	this->playerHpBar.setSize(sf::Vector2f(150.f * hpPercent, this->playerHpBar.getSize().y));
}


void Game::updateBullets()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update();
		//Out of screen
		if (bullets[i]->getBounds().top < 0.f || bullets[i]->getBounds().left < 0.f
			||bullets[i]->getBounds().left + bullets[i]->getBounds().width >= this->window->getSize().x
			||bullets[i]->getBounds().top + bullets[i]->getBounds().height >= this->window->getSize().y)
		{
			std::cout << "Out";
			
			delete this->bullets[i];
			this->bullets.erase(this->bullets.begin() + i);
		}
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->type = rand() % 2;
		if (type == 0)
		{
			pos.x = rand() % this->window->getSize().x - 20.f;
			pos.y = -100.f;
		}
		else if (type == 1)
		{
			pos.x = this->window->getSize().x + 20.f;
			pos.y = rand() % this->window->getSize().y;

		}
		this->enemies.push_back(new Enemy(pos.x, pos.y, &this->enemysprite[this->type], this->type));
		this->spawnTimer = 0.f;
	}
	//ความยากในแต่ละระดับคะแนน
	if (this->points > 100 && this->points <= 200)
	{
		this->spawnTimerMax = 5.f;
	}
	else if (this->points > 200 && this->points <= 700)
	{
		this->spawnTimerMax = 20.f;
	}
	else if (this->points > 700 && this->points <= 3000)
	{
		this->spawnTimerMax = 10.f;
	}
	else if (this->points > 3000)
	{
		this->spawnTimerMax = 5.f;
	}

	//Update
	unsigned counter = 0;
	for (int i = 0; i < enemies.size(); i++)
	{
		//Enemy เกินขอบจอ
		this->enemies[i]->update(this->player->getPos());
		if (this->enemies[i]->getBounds().top > this->window->getSize().y
			|| this->enemies[i]->getBounds().left < 0)
		{
			//Delete enemy
			std::cout << "Destroy";
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
		}
		//Enemy player collision
		else if (this->enemies[i]->getBounds().intersects(this->player->getBounds()))
		{
			
			this->playerCollideSound.play();

			this->player->loseHp(this->enemies[i]->getDamage());
			delete this->enemies[i];
			this->enemies.erase(this->enemies.begin() + i);
			if (this->player->getHp() <= 0) {
				this->updateHigh(this->entername->getPlayerName(), this->points);
			}
		}
	}
}

void Game::updateItem()
{
	//Spawning item
	this->itemSpawnTimer += 0.5f;
	if (this->itemSpawnTimer >= this->itemSpawnTimerMax)
	{
		this->itemSpawnTimer -= this->itemSpawnTimerMax;
		this->randomItem = rand() % 2;
		this->items.push_back(new Item(&this->itemTexture[randomItem], this->window->getSize().x, this->window->getSize().y - ((rand() % this->window->getSize().y - 200) + 100.f), this->randomItem));
		this->itemSpawnTimer = 0.f;
	}

	//Update

	for (int i = 0; i < items.size(); i++)
	{
		this->items[i]->updateItem();
		//Item culling (top of screen)
		if (this->items[i]->deleteItem())
		{
			//Delete Item
			std::cout << "item remove";
			delete this->items[i];
			this->items.erase(this->items.begin() + i);
		}
		//Item player collision
		else if (this->items[i]->getBounds().intersects(this->player->getBounds()))
		{
			this->itemSoundBuffer.loadFromFile("Textures/sounds/1-up.wav");
			this->itemSound.setBuffer(this->itemSoundBuffer);
			this->itemSound.setVolume(30);
			this->itemSound.play();
			if (this->items[i]->itemType() == 0)
			{
				this->player->plusHp(5);
				delete this->items[i];
				this->items.erase(this->items.begin() + i);
			}
			else if (this->items[i]->itemType() == 1)
			{
				this->player->getFireRate();
				delete this->items[i];
				this->items.erase(this->items.begin() + i);
			}
		}
	}
}

void Game::updateCombat()//กระสุนโดน Enemy
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				if (this->type == 0)
				{
					this->points += this->enemies[i]->getPoints() + 5;
				}
				if (this->type == 1)
				{
					this->points += this->enemies[i]->getPoints();
				}


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

	this->updateBullets();

	this->updateEnemies();

	this->updateItem();

	this->updateCombat();

	this->updateGUI();

	//this->updateWorld();

	this->mousePosView = sf::Vector2f(sf::Mouse::getPosition(*window));

}

void Game::updateHigh(std::string name, unsigned int score)
{
	this->fq = fopen("scoreboard/scoreboard.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fq, "%s", &temp);
		this->name[i] = temp;
		fscanf(fq, "%d", &this->score[i]);
		this->userScore.push_back(std::make_pair(this->score[i], this->name[i]));
	}
	this->name[5] = name;
	this->score[5] = score;
	this->userScore.push_back(std::make_pair(this->score[5], this->name[5]));
	std::sort(this->userScore.begin(), this->userScore.end());
	fclose(this->fq);
	this->fq = fopen("scoreboard/scoreboard.txt", "w");
	for (int i = 5; i >= 1; i--)
	{
		fprintf(fq, "%s %d\n", userScore[i].second.c_str(), userScore[i].first);
	}
	fclose(this->fq);
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

	for (auto* Item : this->items)
	{
		Item->render(this->window);
	}

	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0) {
		
		this->window->draw(this->gameOverText);
	}

	this->window->display();
}