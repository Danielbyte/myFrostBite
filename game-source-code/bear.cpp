#include "bear.h"

Bear::Bear():
	bear_direction{Direction::Left}, //Bear initially moving to left
	bear_position{757.5f,199.0f},
	bear_speed{140.0f},
	counter{0}
{
	load_textures();
	spawnPosition = bear_position;
	mSpawnPosition.x = 558.973f;
	mSpawnPosition.y = 199.0f;
	bear_sprite.setOrigin(bear_with / 2.0f, bear_height / 2.0f);
	bear_sprite.setPosition(spawnPosition);
}

void Bear::mSetSpawnPosition()
{
	spawnPosition = mSpawnPosition;
	bear_position = spawnPosition;
	bear_sprite.setPosition(spawnPosition);
}

void Bear::spawnBear()
{
	bear_sprite.setTexture(bear_left1);
	bear_position = spawnPosition;
	bear_sprite.setPosition(spawnPosition);
	counter = 0;
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

void Bear::update_bear(const float deltaTime, Player& player)
{
	set_to_track_player(player);
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

	else if (bear_direction == Direction::unknown)
	{
		bear_sprite.move(0, 0);
	}

	animate_bear();
}

void Bear::animate_bear()
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

void Bear::set_bear_direction(const Direction& direction)
{
	bear_direction = direction;
}

Sprite Bear::getSprite() const
{
	return bear_sprite;
}

void Bear::set_to_track_player(Player& player)
{
	auto timePassed = elapsed_time();

	// Bear should track bailey's position after every 1 second
	if (timePassed >= 2.0f)
	{
		auto PlayerPosition = player.getPosition();
		//get the distance between bear and frostbite
		auto distance_between = abs(PlayerPosition.x - bear_position.x);
		auto safe_zone = player.isPlayerInSafeZone();

		//left and right boundaries
		auto leftBoundary = player.leftBoundary();
		auto rightBoundary = player.rightBoundary();

		//bear should not move if bailey is at the ends of screen
		if (!safe_zone && distance_between <= 31.0f &&
			(PlayerPosition.x <= leftBoundary || PlayerPosition.x >= rightBoundary))
		{
			set_bear_direction(Direction::unknown);
		}

		else
		{
			if (PlayerPosition.x < bear_position.x)
			{
				set_bear_direction(Direction::Left);
			}

			else if (PlayerPosition.x > bear_position.x)
			{
				set_bear_direction(Direction::Right);
			}
		}

		//restart stop watch
		restart_timer();
	}
}