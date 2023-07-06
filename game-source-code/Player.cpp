#include "Player.h"

Player::Player():
	rightPressed{false},
	leftPressed{false},
	upPressed{false},
	downPressed{false},
	gravity{10},
	right_boundary{ 776.0f },
	left_boundary{ 24.0f }
{}

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
	}

	if (upPressed)
	{
		//Frostbite needs to jump up
	}
}

Sprite Player::getSprite() const
{
	return player_sprite;
}
