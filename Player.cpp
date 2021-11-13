#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 2.f;
	this->playerAngle = 0.f;
	this->attackCooldownMax = 5.f;//Bullet rate
	this->attackCooldown = this->attackCooldownMax;
	this->hpMax = 10;
	this->hp = this->hpMax;
	this->itemCoolDownMax = 3000.f;
	this->itemCoolDown = 0.f;
	fireRateflag = false;
}

void Player::initTexture()
{
	//Load a texture from file
	this->texture.loadFromFile("Textures/bill.png");
	
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Resize the sprite
	this->sprite.scale(3.f, 3.f);
	this->sprite.setOrigin(sf::Vector2f(
		this->sprite.getLocalBounds().width / 2,
		this->sprite.getLocalBounds().height / 2)
	);
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{

}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

float& Player::getAngle()
{
	return this->playerAngle;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::plusHp(int hp)
{
	this->hp += hp;
	if (this->hp >= this->hpMax)
	{
		this->hp = this->hpMax;
	}
}

void Player::move(const float dirX, const float dirY, sf::Vector2f mousePosView)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
	//Rotation
	this->mouse_distance = mousePosView - player_position;
	if (mouse_distance.y < 0)
		this->playerAngle = -atanf(mouse_distance.x / mouse_distance.y) * 180.0 / 3.141592;
	else
		this->playerAngle = 180 + -atanf(mouse_distance.x / mouse_distance.y) * 180.0 / 3.141592;
	this->sprite.setRotation(this->playerAngle);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::getFireRate()
{
	this->fireRateflag = true;
}



void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
	{
		//this->attackCooldown += 0.3f;//Bullet speed rate
	}
	if (this->fireRateflag == true) 
	{
		//std::cout << "out";
		if (this->itemCoolDown >= this->itemCoolDownMax)
		{
			this->fireRateflag = false;
			this->itemCoolDown = 0;
			//std::cout << "stop";
		}
		if (this->itemCoolDown < this->itemCoolDownMax)
		{
			this->itemCoolDown += 5.f;
			//std::cout << "rate";
		}

	}
	if (this->fireRateflag == false)
	{
		//std::cout << "0";
		//std::cout << itemCoolDown<<"\n";
		attackCooldown += 0.3f;
		//attackCooldownMax = 5.f;
	}
	else if (this->fireRateflag == true)
	{
		//std::cout << "1";
		attackCooldown += 2.f;
		//std::cout << itemCoolDown << "\n";
		//attackCooldownMax = 2.f;
	}
	//	
	//if (this->fireRateflag == true)
	//{
	//	if (this->attackCooldown < this->attackCooldownMax)
	//	{
	//		//this->fireRateflag = false;
	//		this->attackCooldown += 10.f;//Bullet speed rate
	//	}
	//}
	
	
}

//Functions
void Player::update()
{
	this->updateAttack();
	this->player_position = sprite.getPosition();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}