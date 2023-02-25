#include "crab.h"

Crab::Crab(const int& side, const float& region):
	counter{0},
	cycle{1},
	spawned_left{false},
	spawned_right{false}
{
	pos.y = region;

	if (side == right)
	{
		auto x_position = windowWidth - (crab_width / 2);
		pos.x = x_position;
		spawned_left = false;
		spawned_right = true;
	}

	if (side == left)
	{
		auto x_position = crab_width / 2.0f;
		pos.x = x_position;
		spawned_left = true;
		spawned_right = false;
	}
}

vector2f Crab::get_position() const
{
	return pos;
}

void Crab::set_x_position(const float& x_)
{
	//second crab horizontal position
	//if spawned at the far right
	if (pos.x > (crab_width / 2.0f))
	{
		pos.x -= x_;
	}
	//else spawned at the far left
	else {
		pos.x += x_;
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

std::tuple<bool, bool> Crab::get_spawn_side()
{
	return { spawned_left, spawned_right };
}

void Crab::set_position(const vector2f& pos_)
{
	pos = pos_;
}



