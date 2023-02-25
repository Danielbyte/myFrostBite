#include "bird.h"

Bird::Bird():
	spawned_left{false},
	spawned_right{false}
{}

Bird::Bird(const int& enemySide, const float& region):
	spawned_left{false},
	spawned_right{false}
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
