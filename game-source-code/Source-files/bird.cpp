#include "../Header-files/bird.h"

Bird::Bird():
	counter{0},
	rightP{939.0f},
	leftP{-139.0f},
	mRightP{740.473f},
	mLeftP{61.0f}
{}

Bird::Bird(const int side, const float region, bool isMultiPlayer):
	counter{0},
	rightP{ 939.0f },
	leftP{ -139.0f },
	mRightP{ 740.473f },
	mLeftP{ 61.0f }
{
	position.y = region;
	animal_sprite.setOrigin(bird_width / 2.0f, bird_height / 2.0f);
	if (!isMultiPlayer)
	{
		if (side == right)
		{
			position.x = rightP;
			spawned_right = true;
			animal_sprite.setPosition(position);
		}

		else if (side == left)
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

		else if (side == left)
		{
			position.x = mLeftP;
			spawned_left = true;
			animal_sprite.setPosition(position);
		}
	}
}

void Bird::set_x_position(const float& _x)
{
	if (position.x > (bird_width / 2.0f))
	{
		position.x -= _x;
	}

	else
	{
		position.x += _x;
	}
}

void Bird::increment_counter()
{
	++counter;
}

void Bird::reset_counter()
{
	counter = 0;
}

int Bird::get_counter() const
{
	return counter;
}
