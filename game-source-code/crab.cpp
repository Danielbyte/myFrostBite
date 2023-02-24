#include "crab.h"

Crab::Crab(const int& side, const float& region)
{
	if (side == left)
	{
		auto x_position = windowWidth - (crab_width / 2);
		pos.y = region;
		pos.x = x_position;
	}

	if (side == right)
	{
		std::cout << "Other side!" << std::endl;
	}
}

vector2f Crab::get_position() const
{
	return pos;
}

void Crab::set_x_position(const float& x_)
{
	//second crab horizontal position
	pos.x -= x_;
}




