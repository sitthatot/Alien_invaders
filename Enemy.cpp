#include "Enemy.h"

void Enemy::initVariables()
{
	this->pointCount = 5; //min = 3 max = 10
	this->type = 0;
	this->speed = static_cast<float>(this->pointCount / 3);
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
}

void Enemy::initTexture()
{
	this->texture.loadFromFile("Textures/aliena.png");
}

void Enemy::initSprite()
{
	this->sprite.setTexture(this->texture);
	//Resize the sprite
	this->sprite.scale(3.f, 3.f);
	this->sprite.setOrigin(sf::Vector2f(
		this->sprite.getLocalBounds().width / 2,
		this->sprite.getLocalBounds().height / 2)
	);
}

void Enemy::initShape()
{
	//Set the texture to the sprite
	
	
	
	/*
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
	*/
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	//this->initShape();
	
	//this->shape.setPosition(pos_x, pos_y);
	this->sprite.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

//Accessors
const sf::FloatRect Enemy::getBounds() const
{
	//return this->shape.getGlobalBounds();
	return this->sprite.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

//Functions
void Enemy::update()
{
	//this->shape.move(0.f, this->speed);
	this->sprite.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	//target->draw(this->shape);
	target->draw(this->sprite);
}