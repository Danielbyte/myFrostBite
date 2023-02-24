#include "fish.h"

Fish::Fish(const int& side, const float& region)
{
	pos.y = region;
	if (side == right)
	{
		pos.x = windowWidth - (fish_width / 2.0f);
	}
	else if (side == left)
	{
		pos.x = fish_width / 2.0f;
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
