#include "bird.h"

Bird::Bird():
	counter{0}
{}

Bird::Bird(const int& side, const float& region):
	counter{0}
{
	position.y = region;
	auto gapBetweenBirds = 120.0f;
	animal_sprite.setOrigin(bird_width / 2.0f, bird_height / 2.0f);

	if (side == right)
	{
		position.x = windowWidth + (bird_width / 2.0f) + gapBetweenBirds;
		spawned_right = true;
		animal_sprite.setPosition(position);
	}

	else if (side == left)
	{
		position.x = (-bird_width / 2.0f) - gapBetweenBirds;
		spawned_left = true;
		animal_sprite.setPosition(position);
	}
}

void Bird::set_x_position(const float& _x)
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

void Bird::increment_counter()
{
	++counter;
}

void Bird::reset_counter()
{
	counter = 0;
}

int Bird::get_counter() const
{
	return counter;
}
