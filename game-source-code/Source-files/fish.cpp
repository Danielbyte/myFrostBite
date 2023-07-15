#include "../Header-files/fish.h"

Fish::Fish():
	counter{ 0 },
	RinitPosition{951.5f},
	LinitPosition{-151.5f},
	mRInitPosition{752.973f},
	mLInitPosition{48.5f}
{}

Fish::Fish(const int side, const float region, bool isMultiplayer):
	counter {0},
	RinitPosition{ 951.5f },
	LinitPosition{ -151.5f },
	mRInitPosition{ 752.973f },
	mLInitPosition{ 48.5f }
{
	position.y = region;
	if (!isMultiplayer)
	{
		animal_sprite.setOrigin(fish_width / 2.0f, fish_height / 2.0f);
		if (side == right)
		{
			position.x = RinitPosition;
			spawned_right = true;
			animal_sprite.setPosition(position);
		}
		else if (side == left)
		{
			position.x = LinitPosition;
			spawned_left = true;
			animal_sprite.setPosition(position);
		}
		return;
	}
	else
	{
		auto gapBetweenFish = 130.0f;
		animal_sprite.setOrigin(fish_width / 2.0f, fish_height / 2.0f);
		if (side == right)
		{
			position.x = mRInitPosition;
			spawned_right = true;
			animal_sprite.setPosition(position);
		}
		else if (side == left)
		{
			position.x = mLInitPosition;
			spawned_left = true;
			animal_sprite.setPosition(position);
		}
	}

}

void Fish::set_x_position(const float& _x)
{
	if (position.x > (fish_width / 2.0f))
	{
		position.x -= _x;
	}

	else
	{
		position.x += _x;
	}
}

int Fish::get_counter() const
{
	return counter;
}

void Fish::reset_counter()
{
	counter = 0;
}

void Fish::increment_counter()
{
	++counter;
}