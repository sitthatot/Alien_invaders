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
	this->sprite.setRotation(180.f);
	this->sprite.scale(3.f, 3.f);
	this->sprite.setOrigin(sf::Vector2f(
		this->sprite.getLocalBounds().width / 2,
		this->sprite.getLocalBounds().height / 2)
	);
}

Enemy::Enemy(float pos_x, float pos_y, sf::Texture* texture, int type)
{
	this->initVariables();
	this->initSprite();
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->type = type;
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
const sf::Vector2f& Enemy::getEnemyPos() const
{
	return this->sprite.getPosition();
}

//Functions
void Enemy::update(sf::Vector2f playerPos)
{
	this->playerPos = playerPos;
	if (type == 0) 
	{
		this->sprite.move(0.f, this->speed);
	}
	else if (type == 1)
	{
		if (this->playerPos.y > this->getEnemyPos().y)
		{
			this->sprite.move(-this->speed, 1.f);
		}
		else if (this->playerPos.y < this->getEnemyPos().y)
		{
			this->sprite.move(-this->speed, -1.f);
		}
		else if (this->playerPos.y == this->getEnemyPos().y)
		{
			this->sprite.move(-this->speed, 0.f);
		}
	}
}

void Enemy::render(sf::RenderTarget* target)
{
	//target->draw(this->shape);
	target->draw(this->sprite);
}