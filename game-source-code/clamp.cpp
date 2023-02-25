#include "clamp.h"

Clamp::Clamp():
	counter{ 0 },
	cycle{ 1 },
	spawned_left{ false },
	spawned_right{ false }
{}

Clamp::Clamp(const int& side, const float& region):
	counter{0},
	cycle{1},
	spawned_left{false},
	spawned_right{false}
{
	pos.y = region;
	auto gapBetweenClamps = 120.0f;
	if (side == right)
	{
		auto x_position = windowWidth + (clamp_width / 2) + gapBetweenClamps;
		pos.x = x_position;
		spawned_right = true;
	}

	if (side == left)
	{
		auto x_position = (-clamp_width / 2.0f) - gapBetweenClamps;
		pos.x = x_position;
		spawned_left = true;
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

int Clamp::get_cycle() const
{
	return cycle;
}

void Clamp::increment_cycle()
{
	++cycle;
}

void Clamp::reset_cycle()
{
	cycle = 1;
}

int Clamp::get_counter() const
{
	return counter;
}

void Clamp::increment_counter()
{
	++counter;
}

void Clamp::reset_counter()
{
	counter = 0;
}

void Clamp::set_postion(const vector2f& _pos)
{
	pos = _pos;
}

std::tuple<bool, bool> Clamp::get_side()
{
	return { spawned_left, spawned_right };
}

