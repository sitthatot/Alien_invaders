#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;
	float playerAngle;
	float attackCooldown;
	float attackCooldownMax;
	//position
	sf::Vector2f player_position;
	sf::Vector2f mouse_distance;
	int hp;
	int hpMax;

	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();

public:
	Player();
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	float& getAngle();
	const int& getHp() const;
	const int& getHpMax() const;

	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);
	void plusHp(int hp);
	//Functions
	void move(const float dirX, const float dirY, sf::Vector2f mousePosView);
	const bool canAttack();

	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};