#include "bird.h"

Bird::Bird():
	spawned_left{false},
	spawned_right{false},
	counter{0}
{}

Bird::Bird(const int& enemySide, const float& region):
	spawned_left{false},
	spawned_right{false},
	counter{0}
{
	pos.y = region;
	if (enemySide == right)
	{
		pos.x = windowWidth - (bird_width / 2.0f);
		spawned_right = true;
	}

	else if (enemySide == left)
	{
		pos.x = (bird_width / 2.0f);
		spawned_left = true;
	}
}

vector2f Bird::get_position() const
{
	return pos;
}

void Bird::set_x_position(const float& _x)
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

vector2f Bird::get_position() const
{
	return pos;
}

void Bird::set_position(const vector2f& pos_)
{
	pos = pos_;
}

std::tuple<bool, bool> Bird::get_side()
{
	return { spawned_left, spawned_right };
}
