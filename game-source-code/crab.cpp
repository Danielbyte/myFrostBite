#include "crab.h"

Crab::Crab():
	counter{ 0 },
	cycle{ 1 },
	rightP{941.0f},
	leftP{-141.0f},
	mRightP{742.473f},
	mLeftP{59.0f}
{}

Crab::Crab(const int side, const float region, bool isMultiPlayer):
	counter{0},
	cycle{1},
	rightP{ 941.0f },
	leftP{ -141.0f },
	mRightP{ 742.473f },
	mLeftP{ 59.0f }
{
	position.y = region;
	if (!isMultiPlayer)
	{
		auto gapBetweeenCrabs = 120.0f;
		animal_sprite.setOrigin(crab_width / 2.0f, crab_height / 2.0f);
		if (side == right)
		{
			position.x = rightP;
			spawned_left = false;
			spawned_right = true;
			animal_sprite.setPosition(position);
		}

		if (side == left)
		{
			position.x = leftP;
			spawned_left = true;
			spawned_right = false;
			animal_sprite.setPosition(position);
		}

		return;
	}

	else
	{
		auto gapBetweeenCrabs = 120.0f;
		animal_sprite.setOrigin(crab_width / 2.0f, crab_height / 2.0f);
		if (side == right)
		{
			position.x = mRightP;
			spawned_left = false;
			spawned_right = true;
			animal_sprite.setPosition(position);
		}

		if (side == left)
		{
			position.x = mLeftP;
			spawned_left = true;
			spawned_right = false;
			animal_sprite.setPosition(position);
		}
	}

}

void Crab::set_x_position(const float& x_)
{
	//second crab horizontal position
	//if spawned at the far right
	if (position.x > (crab_width / 2.0f))
	{
		position.x -= x_;
	}
	//else spawned at the far left
	else {
		position.x += x_;
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

int Crab::get_cycle() const
{
	return cycle;
}

void Crab::increment_cycle()
{
	++cycle;
}

void Crab::reset_cycle()
{
	cycle = 1;
}


