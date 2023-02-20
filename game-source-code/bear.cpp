#include "bear.h"

Bear::Bear():
	bear_direction{Direction::Left}, //Bear initially moving to left
	bear_position{757.5f,199.0f},
	bear_speed{110.0f}
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
}