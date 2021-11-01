#include "Enemy_ball.h"

void Enemy_2::initVariables()
{
	this->pointCount = 5; //min = 3 max = 10
	this->type = 0;
	this->speed = static_cast<float>(this->pointCount / 3);
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
}

void Enemy_2::initTexture()
{
	this->texture.loadFromFile("Textures/roboball.png");
}

void Enemy_2::initSprite()
{
	this->sprite.setTexture(this->texture);
	//Resize the sprite
	this->sprite.scale(3.f, 3.f);
	this->sprite.setOrigin(sf::Vector2f(
		this->sprite.getLocalBounds().width / 2,
		this->sprite.getLocalBounds().height / 2)
	);
}

Enemy_2::Enemy_2(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	//this->initShape();

	//this->shape.setPosition(pos_x, pos_y);
	this->sprite.setPosition(pos_x, pos_y);
}

Enemy_2::~Enemy_2()
{

}

//Accessors
const sf::FloatRect Enemy_2::getBounds() const
{
	//return this->shape.getGlobalBounds();
	return this->sprite.getGlobalBounds();
}

const int& Enemy_2::getPoints() const
{
	return this->points;
}

const int& Enemy_2::getDamage() const
{
	return this->damage;
}

//Functions
void Enemy_2::update()
{
	//this->shape.move(0.f, this->speed);
	this->sprite.move(0.f, this->speed);
}

void Enemy_2::render(sf::RenderTarget* target)
{
	//target->draw(this->shape);
	target->draw(this->sprite);
}