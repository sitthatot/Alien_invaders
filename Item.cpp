#include "Item.h"

Item::Item(sf::Texture* texture, float PosX, float PosY, int type)
{
	this->itemTexture = texture;
	this->itemSprite.setTexture(*this->itemTexture);
	this->itemSprite.setPosition(PosX, PosY);
	this->type = type;
	this->timerMax = 400;
	this->timer = 0;
}

Item::~Item()
{

}

const sf::FloatRect Item::getBounds() const
{
	return this->itemSprite.getGlobalBounds();
}

const bool Item::deleteItem()
{
	if (this->itemSprite.getPosition().x < 50)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Item::updateItem()
{
	this->itemSprite.move(-3, 0);
}

void Item::render(sf::RenderTarget* target)
{
	target->draw(this->itemSprite);
}