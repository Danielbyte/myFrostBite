#include "../Header-files/clamp.h"

Clamp::Clamp():
	counter{ 0 },
	cycle{ 1 },
	rightP{941.0f},
	leftP{-141.0f},
	mRightP{742.473f},
	mLeftP{59.0f}
{}

Clamp::Clamp(const int side, const float region, bool isMultiPlayer):
	counter{0},
	cycle{1},
	rightP{ 941.0f },
	leftP{ -141.0f },
	mRightP{ 742.473f },
	mLeftP{ 59.0f }
{
	position.y = region;
	animal_sprite.setOrigin(clamp_width / 2.0f, clamp_height / 2.0f);

	if (!isMultiPlayer)
	{
		if (side == right)
		{
			position.x = rightP;
			spawned_right = true;
			animal_sprite.setPosition(position);
		}

		if (side == left)
		{
			position.x = leftP;
			spawned_left = true;
			animal_sprite.setPosition(position);
		}

		return;
	}

	else
	{
		if (side == right)
		{
			position.x = mRightP;
			spawned_right = true;
			animal_sprite.setPosition(position);
		}

		if (side == left)
		{
			position.x = mLeftP;
			spawned_left = true;
			animal_sprite.setPosition(position);
		}
	}
}

void Clamp::set_x_position(const float& _x)
{
	if (position.x > clamp_width / 2.0f)
	{
		position.x -= _x;
	}

	else
	{
		position.x += _x;
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

