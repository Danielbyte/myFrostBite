#include "Player.h"

Player::Player():
	rightPressed{false},
	leftPressed{false},
	upPressed{false},
	downPressed{false},
	playerJumping{ false },
	gravity{10.0f},
	right_boundary{ 776.0f },
	left_boundary{ 24.0f },
	speed{0.0f},
	speed_attenuater{ 0.2f },
	distance_between_iceRows{ 82.0f },
	Region1{ 281.0f },
	Region2{ 363.0f },
	Region3{ 445.0f },
	Region4{ 527.0f },
	safe_zone_boundary{ 199.0f },
	JumpForce{ 80.0f },
	player_mass{75.0f}
{
	bailey_region = PlayerRegion::unknown; //bailey initially not in any of the four regions
}

void Player::spawnPlayer(vector2f initPosition)
{
	position.x = initPosition.x;
	position.y = initPosition.y;
	player_sprite.setOrigin(bailey_width / 2.0, bailey_height / 2.0);
	player_sprite.setPosition(position);
	player_sprite.setTexture(player_texture);
}

void Player::update(float timeElapsed)
{
	if (rightPressed)
	{
		position.x += 180 * timeElapsed;
		player_sprite.setPosition(position);

        if (position.x >= right_boundary)
        {
	      position.x = right_boundary;
	      player_sprite.setPosition(position);
        }
	}

	if (leftPressed)
	{

        // move player
		position.x -= 180 * timeElapsed;
		player_sprite.setPosition(position);

        //restrict player within screen
        if (position.x <= left_boundary)
        {
     	 position.x = left_boundary;
	     player_sprite.setPosition(position);
        }
	}

	if (downPressed)
	{
		//Frostbite needs to jump down
		jump_down(timeElapsed, position.y);
	}

	if (upPressed)
	{
		//Frostbite needs to jump up
	}
}

void Player::jump_down(const float& deltaTime, const float start_position)
{
	speed = JumpForce / player_mass;
	speed -= gravity * deltaTime * speed_attenuater;
	player_sprite.move(0, -speed);
	position.y = player_sprite.getPosition().y;//update vertical position
	auto jumped_distance = position.y - start_position;//calculate total distance jumped by frostbite
	//is_bailey_jumping = isJumping;
	
	if (jumped_distance > distance_between_iceRows)
	{
		//frostbite jumps betweent consecutive rows of ice
		position.y = start_position + distance_between_iceRows;
		calibrate();
		player_sprite.setPosition(position);
		//isJumping = false;//frostbite has stepped on ice row or drowned
		//isJumpingDown = false;
		//is_bailey_jumping = false;
		downPressed = false;
		update_bailey_region();
	}
}

void Player::calibrate()
{
	if (position.y >= 280.0f && position.y <= 281.0f)
	{
		position.y = 281.0f;
	}

}

void Player::update_bailey_region()
{
	if (position.y == Region1)
	{
		bailey_region = PlayerRegion::region1;
	}

	if (position.y == Region2)
	{
		bailey_region = PlayerRegion::region2;
	}

	if (position.y == Region3)
	{
		bailey_region = PlayerRegion::region3;
	}

	if (position.y == Region4)
	{
		bailey_region = PlayerRegion::region4;
	}

	if (position.y <= safe_zone_boundary || position.y > Region4)
	{
		bailey_region = PlayerRegion::unknown;
	}
}

Sprite Player::getSprite() const
{
	return player_sprite;
}
