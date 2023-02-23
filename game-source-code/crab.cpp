#include "crab.h"

Crab::Crab(const int& side, const float& region)
{
	if (side == left)
	{
		auto x_position = windowWidth - (crab_width / 2);
		pos.y = region;
		pos.x = x_position;
	}
}

vector2f Crab::get_position() const
{
	return pos;
}




