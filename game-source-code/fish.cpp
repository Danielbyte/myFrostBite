#include "fish.h"

Fish::Fish():
	counter{ 0 }
{}

Fish::Fish(const int& side, const float& region):
	counter {0}
{
	position.y = region;
	auto gapBetweenFish = 130.0f;
	animal_sprite.setOrigin(fish_width / 2.0f, fish_height / 2.0f);
	if (side == right)
	{
		position.x = windowWidth + (fish_width / 2.0f) + gapBetweenFish;
		spawned_right = true;
		animal_sprite.setPosition(position);
	}
	else if (side == left)
	{
		position.x = (-fish_width / 2.0f) - gapBetweenFish;
		spawned_left = true;
		animal_sprite.setPosition(position);
	}
}

void Fish::set_x_position(const float& _x)
{
	if (position.x > (fish_width / 2.0f))
	{
		position.x -= _x;
	}

	else
	{
		position.x += _x;
	}
}

int Fish::get_counter() const
{
	return counter;
}

void Fish::reset_counter()
{
	counter = 0;
}

void Fish::increment_counter()
{
	++counter;
}