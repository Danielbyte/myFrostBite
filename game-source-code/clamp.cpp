#include "clamp.h"

Clamp::Clamp(const int& side, const float& region)
{
	if (side == right)
	{
		auto x_position = windowWidth - (clamp_width / 2);
		pos.y = region;
		pos.x = x_position;
	}

	if (side == left)
	{
		auto x_position = clamp_width / 2.0f;
		pos.y = region;
		pos.x = x_position;
	}
}

vector2f Clamp::get_position() const
{
	return pos;
}

void Clamp::set_x_position(const float& _x)
{
	if (pos.x > clamp_width / 2.0f)
	{
		pos.x -= _x;
	}

	else
	{
		pos.x += _x;
	}
}

