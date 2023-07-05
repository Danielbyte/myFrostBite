#include "Animal.h"

Animal::Animal():
	spawned_left{false},
	spawned_right{false}
{}

vector2f Animal::getPosition() const
{
	return position;
}

std::tuple<bool, bool> Animal::getSide() const
{
	return { spawned_left, spawned_right };
}

void Animal::setPosition(const vector2f _position)
{
	position = _position;
}

Sprite Animal::getSprite() const
{
	return animal_sprite;
}

void Animal::updateSpritePosition()
{
	animal_sprite.setPosition(position);
}

void Animal::updateSpriteTexture(const Texture& _texture)
{
	animal_sprite.setTexture(_texture);
}