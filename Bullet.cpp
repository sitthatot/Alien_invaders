#define _CRT_SECURE_NO_WARNINGS
#include "Bullet.h"
#include <cmath>

Bullet::Bullet()
{

}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed, float playerAngle)//constructor
{
	//Method
	this->shape.setTexture(*texture);
	this->shape.scale(0.02f, 0.02f);
	this->shape.setPosition(pos_x, pos_y);
	this->angle = playerAngle;
	this->direction.x = dir_x * sinf(angle * 3.141592/180);
	this->direction.y = dir_y * -cosf(angle * 3.141592 / 180);;
	this->movementSpeed = movement_speed;
	
}

Bullet::~Bullet()
{

}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Bullet::update()
{
	//Movement
	this->shape.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}