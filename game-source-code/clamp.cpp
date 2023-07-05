#include "clamp.h"

Clamp::Clamp():
	counter{ 0 },
	cycle{ 1 }
{}

Clamp::Clamp(const int& side, const float& region):
	counter{0},
	cycle{1}
{
	position.y = region;
	auto gapBetweenClamps = 120.0f;
	animal_sprite.setOrigin(clamp_width / 2.0f, clamp_height / 2.0f);
	if (side == right)
	{
		auto x_position = windowWidth + (clamp_width / 2) + gapBetweenClamps;
		position.x = x_position;
		spawned_right = true;
		animal_sprite.setPosition(position);
	}

	if (side == left)
	{
		auto x_position = (-clamp_width / 2.0f) - gapBetweenClamps;
		position.x = x_position;
		spawned_left = true;
		animal_sprite.setPosition(position);
	}
}

void Clamp::set_x_position(const float& _x)
{
	if (position.x > clamp_width / 2.0f)
	{
		position.x -= _x;
	}

	else
	{
		position.x += _x;
	}
}

int Clamp::get_cycle() const
{
	return cycle;
}

void Clamp::increment_cycle()
{
	++cycle;
}

void Clamp::reset_cycle()
{
	cycle = 1;
}

int Clamp::get_counter() const
{
	return counter;
}

void Clamp::increment_counter()
{
	++counter;
}

void Clamp::reset_counter()
{
	counter = 0;
}

