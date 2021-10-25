#ifndef ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>

class Enemy
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	unsigned pointCount;
	sf::CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initVariables();
	void initTexture();
	void initSprite();
	void initShape();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Accessors
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	//Functions
	void update();
	void render(sf::RenderTarget* target);
};

#endif //!ENEMY_H