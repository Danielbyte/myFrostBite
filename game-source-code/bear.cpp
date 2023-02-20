#include "bear.h"

Bear::Bear():
	bear_direction{Direction::Left}, //Bear initially moving to left
	bear_position{757.5f,199.0f},
	bear_speed{140.0f},
	counter{0}
{
	load_textures();
}

vector2f Bear::get_position() const
{
	return bear_position;
}

void Bear::load_textures()
{
	bear_left1.loadFromFile("resources/bear1_left.png");
	bear_left2.loadFromFile("resources/bear2_left.png");
	bear_left3.loadFromFile("resources/bear3_left.png");
	bear_right1.loadFromFile("resources/bear1_right.png");
	bear_right2.loadFromFile("resources/bear2_right.png");
	bear_right3.loadFromFile("resources/bear3_right.png");
}

void Bear::update_bear(Sprite& bear_sprite, const float& deltaTime)
{
	if (bear_direction == Direction::Left)
	{
		bear_sprite.move(-bear_speed * deltaTime, 0);
		bear_position = bear_sprite.getPosition();

		//restrict bear to left border
		if (bear_position.x <= 42.5f)
		{
			bear_position.x = 42.5f;
			bear_sprite.setPosition(bear_position);
			bear_direction = Direction::Right;
		}
	}

	else if (bear_direction == Direction::Right)
	{
		bear_sprite.move(bear_speed * deltaTime, 0);
		bear_position = bear_sprite.getPosition();

		//restrict bear to right border
		if (bear_position.x >= 757.5f)
		{
			bear_position.x = 757.5f;
			bear_sprite.setPosition(bear_position);
			bear_direction = Direction::Left;
		}

	}

	animate_bear(bear_sprite);
}

void Bear::animate_bear(Sprite& bear_sprite)
{
	if (bear_direction == Direction::Left)
	{
		increment_counter();
		if (counter <= 8)
		{
			bear_sprite.setTexture(bear_left1);
		}

		else if (counter > 8 && counter <= 16)
		{
			bear_sprite.setTexture(bear_left2);
		}

		else if (counter > 16 && counter <= 24)
		{
			bear_sprite.setTexture(bear_left3);
			reset_counter();
		}
	}

	else if (bear_direction == Direction::Right)
	{
		increment_counter();
		if (counter <= 8)
		{
			bear_sprite.setTexture(bear_right1);
		}

		else if (counter > 8 && counter <= 16)
		{
			bear_sprite.setTexture(bear_right2);
		}

		else if (counter > 16 && counter <= 24)
		{
			bear_sprite.setTexture(bear_right3);
			reset_counter();
		}
	}
}

void Bear::reset_counter()
{
	counter = 0;
}

void Bear::increment_counter()
{
	++counter;
}