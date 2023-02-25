#include "fish.h"

Fish::Fish():
	spawned_left{ false },
	spawned_right{ false },
	counter{ 0 }
{}

Fish::Fish(const int& side, const float& region):
	spawned_left{false},
	spawned_right{ false },
	counter {0}
{
	pos.y = region;
	if (side == right)
	{
		pos.x = windowWidth - (fish_width / 2.0f);
		spawned_right = true;
	}
	else if (side == left)
	{
		pos.x = fish_width / 2.0f;
		spawned_left = true;
	}
}

vector2f Fish::get_position() const
{
	return pos;
}

void Fish::set_x_position(const float& _x)
{
	if (pos.x > (fish_width / 2.0f))
	{
		pos.x -= _x;
	}

	else
	{
		pos.x += _x;
	}
}

std::tuple<bool, bool> Fish::get_side()
{
	return { spawned_left, spawned_right };
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
