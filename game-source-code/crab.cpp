#include "crab.h"

Crab::Crab():
	counter{ 0 },
	cycle{ 1 }
{}

Crab::Crab(const int& side, const float& region):
	counter{0},
	cycle{1}
{
	position.y = region;
	auto gapBetweeenCrabs = 120.0f;
	animal_sprite.setOrigin(crab_width / 2.0f, crab_height / 2.0f);
	if (side == right)
	{
		auto x_position = windowWidth + (crab_width / 2) + gapBetweeenCrabs;
		position.x = x_position;
		spawned_left = false;
		spawned_right = true;
		animal_sprite.setPosition(position);
	}

	if (side == left)
	{
		auto x_position = (- crab_width / 2.0f) - gapBetweeenCrabs;
		position.x = x_position;
		spawned_left = true;
		spawned_right = false;
		animal_sprite.setPosition(position);
	}
}

void Crab::set_x_position(const float& x_)
{
	//second crab horizontal position
	//if spawned at the far right
	if (position.x > (crab_width / 2.0f))
	{
		position.x -= x_;
	}
	//else spawned at the far left
	else {
		position.x += x_;
	}
	
}

void Crab::increment_counter()
{
	++counter;
}

void Crab::reset_counter()
{
	counter = 0;
}

int Crab::get_counter() const
{
	return counter;
}

int Crab::get_cycle() const
{
	return cycle;
}

void Crab::increment_cycle()
{
	++cycle;
}

void Crab::reset_cycle()
{
	cycle = 1;
}


