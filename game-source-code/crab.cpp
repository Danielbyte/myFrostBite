#include "crab.h"

Crab::Crab(const int& side, const float& region):
	counter{0}
{
	pos.y = region;

	if (side == right)
	{
		auto x_position = windowWidth - (crab_width / 2);
		pos.x = x_position;
	}

	if (side == left)
	{
		auto x_position = crab_width / 2.0f;
		pos.x = x_position;
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




