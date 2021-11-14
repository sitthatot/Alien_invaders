#define _CRT_SECURE_NO_WARNINGS 1
#include "Highscore.h"

void Highscore::initHighscore()
{
	this->font.loadFromFile("Fonts/AGoblinAppears-o2aV.ttf");
	this->scoreBoardText.setFont(this->font);
	this->scoreBoardText.setCharacterSize(40);
	this->scoreBoardText.setFillColor(sf::Color::White);
	this->scoreBoardText.setString("Leader Board");
	this->scoreBoardText.setPosition((this->windowX / 2) - (this->scoreBoardText.getGlobalBounds().width / 2), 50);
	this->high = fopen("scoreboard/scoreboard.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(high, "%s", &temp);
		name[i] = temp;
		fscanf(high, "%d", &score[i]);
		this->userScore.push_back(std::make_pair(this->score[i], this->name[i]));
	}
	fclose(this->high);
	for (int i = 0; i < 5; i++)
	{
		this->playerName[i].setString(this->name[i]);
		this->playerScore[i].setString(std::to_string(this->score[i]));
		this->playerName[i].setFont(this->font);
		this->playerName[i].setCharacterSize(30);
		this->playerName[i].setFillColor(sf::Color::White);
		this->playerName[i].setPosition((this->windowX / 2) - (this->scoreBoardText.getGlobalBounds().width / 2), 200 + 100 * i);
		this->playerScore[i].setFont(this->font);
		this->playerScore[i].setCharacterSize(30.f);
		this->playerScore[i].setFillColor(sf::Color::White);
		this->playerScore[i].setPosition((this->windowX / 2) + (this->scoreBoardText.getGlobalBounds().width / 2), 200 + 100 * i);
	}
}

void Highscore::initBackground()
{
	this->backgroundTexture.loadFromFile("Textures/score_bg.JPG");
	this->background.setTexture(this->backgroundTexture);
}

Highscore::Highscore(sf::RenderWindow* window)
{
	this->window = window;
	this->initHighscore();
	this->initBackground();
}

Highscore::~Highscore()
{
	this->backgroundTexture;
	this->background;
}

void Highscore::render()
{
	this->window->clear();
	std::cout << "A";
	this->window->draw(this->background);
	this->window->draw(this->scoreBoardText);

	for (int i = 0; i < 5; i++)
	{
		this->window->draw(this->playerName[i]);
		this->window->draw(this->playerScore[i]);
	}
	this->window->display();
}
