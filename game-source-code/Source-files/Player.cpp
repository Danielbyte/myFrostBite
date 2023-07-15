#include "../Header-files/Player.h"

Player::Player():
	rightPressed{false},
	leftPressed{false},
	upPressed{false},
	downPressed{false},
	playerJumping{ false },
	reverseBtnPressed{false},
	playerInSafeZone{ true },
	gravity{10.0f},
	right_boundary{ 776.0f },
	left_boundary{ 24.0f },
	speed{0.0f},
	speed_attenuater{ 1.5f },
	distance_between_iceRows{ 82.0f },
	Region1{ 281.0f },
	Region2{ 363.0f },
	Region3{ 445.0f },
	Region4{ 527.0f },
	safe_zone_boundary{ 199.0f },
	downJumpForce{ 80.0f },
	player_mass{75.0f},
	prevRegion{0.0f},
	isJumpingDown{false},
	isJumpingUp{false},
	upJumpForce{ 410.0f },
	playerMoving{false},
	facingRight{false},
	facingLeft{false},
	new_speed{ 88.5f },
	numberOfLives{3}, //Player has 3 lives
    won{false},
	blueIce{0}
{
	initialPosition.y = 199.0f;
	initialPosition.x = 224.0f;
	player_region = PlayerRegion::unknown; //bailey initially not in any of the four regions
	state = PlayerState::Alive;
	playerWatch.stop_timer();
}

void Player::setState(PlayerState _state)
{
	state = _state;
}

PlayerState Player::getState()
{
	return state;
}

void Player::incrementBlueIce()
{
	++blueIce;
}

int Player::NumberOfBlueIceSteepedOn() const
{
	return blueIce;
}

void Player::resetBlueIce()
{
	blueIce = 0;
}

void Player::spawnPlayer()
{
	position= initialPosition;
	player_sprite.setOrigin(bailey_width / 2.0, bailey_height / 2.0);
	player_sprite.setPosition(position);
	player_texture.loadFromFile("resources/bailey.png");
	player_sprite.setTexture(player_texture);
	prevPosition = initialPosition;
}

void Player::setInitialPosition(vector2f _position)
{
	initialPosition = _position;
}

void Player::setBoundaries(const float leftB, const float rightB)
{
	left_boundary = leftB;
	right_boundary = rightB;
}

int Player::getNumberOfLives() const
{
	return numberOfLives;
}

void Player::update(float timeElapsed)
{
	if (rightPressed)
	{
		position.x += 180 * timeElapsed;
		player_sprite.setPosition(position);
		facingRight = true;
		facingLeft = false;

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
		facingRight = false;
		facingLeft = true;

        //restrict player within screen
        if (position.x <= left_boundary)
        {
     	 position.x = left_boundary;
	     player_sprite.setPosition(position);
        }
	}

	if (downPressed && !playerJumping)
	{
		//Frostbite needs to jump down
		playerJumping = true;
		isJumpingDown = true;
		setSpeed(downJumpForce);
		prevRegion = position.y;
	}

	if (upPressed && !playerJumping)
	{
		//Frostbite needs to jump up
		playerJumping = true;
		isJumpingUp = true;
		setSpeed(upJumpForce);
		prevRegion = position.y;
	}

	if (playerJumping && isJumpingDown) { jump_down(timeElapsed, prevRegion); }
	if (playerJumping && isJumpingUp) { jump_up(timeElapsed, prevRegion); }
}

void Player::jump_down(const float& deltaTime, const float start_position)
{
	speed -= gravity * deltaTime * speed_attenuater;
	player_sprite.move(0, -speed);
	position.y = player_sprite.getPosition().y;//update vertical position
	auto jumped_distance = position.y - start_position;//calculate total distance jumped by frostbite
	
	if (jumped_distance > distance_between_iceRows)
	{
		//frostbite jumps betweent consecutive rows of ice
		position.y = start_position + distance_between_iceRows;
		calibrate();
		player_sprite.setPosition(position);
		downPressed = false;
		playerJumping = false;
		isJumpingDown = false;
		update_bailey_region();
	}
}

void Player::jump_up(const float deltaTime, const float start_position)
{

	if (position.y > safe_zone_boundary)
	{
		speed -= gravity * deltaTime;
		player_sprite.move(0, -speed);
		position.y = player_sprite.getPosition().y;
		auto jumped_distance = start_position - position.y;

		if (speed < 0 && position.y >= (start_position - distance_between_iceRows))
		{
			position.y = start_position - distance_between_iceRows;
			player_sprite.setPosition(position);
			playerJumping = false;
			isJumpingUp = false;
			upPressed = false;
			update_bailey_region();
		}
	}

	else if (position.y <= safe_zone_boundary)
	{
		playerJumping = false;
		upPressed = false;
		isJumpingUp = false;
	}
}

void Player::setSpeed(const float _Force)
{
	speed = _Force / player_mass;
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
		player_region = PlayerRegion::region1;
	}

	if (position.y == Region2)
	{
		player_region = PlayerRegion::region2;
	}

	if (position.y == Region3)
	{
		player_region = PlayerRegion::region3;
	}

	if (position.y == Region4)
	{
		player_region = PlayerRegion::region4;
	}

	if (position.y <= safe_zone_boundary || position.y > Region4)
	{
		player_region = PlayerRegion::unknown;
	}
}

Sprite Player::getSprite() const
{
	return player_sprite;
}

bool Player::IsplayerMoving()
{
	if (prevPosition == position)
	{
		playerMoving = false;
	}
	else
	{
		prevPosition = position;
		playerMoving = true;
	}

	return playerMoving;
}

bool Player::isRightPressed() const
{
	return rightPressed;
}

bool Player::isLeftPressed() const
{
	return leftPressed;
}

bool Player::isPlayerJumping() const
{
	return playerJumping;
}

bool Player::isFacingRight() const
{
	return facingRight;
}

bool Player::getIfWon()
{
	return won;
}

void Player::setToWin()
{
	won = true;
}

bool Player::isFacingLeft() const
{
	return facingLeft;
}

vector2f Player::getPosition() const
{
	return position;
}

void Player::updateSprite(Texture& newTexture)
{
	player_sprite.setTexture(newTexture);
}

bool Player::isPlayerInSafeZone()
{
	if (position.y > safe_zone_boundary) { playerInSafeZone = false; }
	else if (position.y <= safe_zone_boundary && !playerJumping) { playerInSafeZone = true; }
	return playerInSafeZone;
}

void Player::setPlayerToMoveWithIce(const Direction& dir, const float deltaTime)
{
	switch (dir)
	{
	case Direction::Left:
		player_sprite.move(-new_speed * deltaTime, 0);
		//update frostbite's horizontal direction
		position = player_sprite.getPosition();

		//Restrict frostbite to left screen border
		if (position.x <= left_boundary)
		{
			position.x = left_boundary;
			player_sprite.setPosition(position);
		}
		break;

	case Direction::Right:
		player_sprite.move(new_speed * deltaTime, 0);
		position = player_sprite.getPosition();
		if (position.x >= right_boundary)
		{
		    position.x = right_boundary;
			player_sprite.setPosition(position);
		}
		break;

	    default:
		break;
	}

}

void Player::subractLive()
{
	if (numberOfLives >= 1)
	{
		--numberOfLives;
	}
}

void Player::restartWatch()
{
	playerWatch.restart_timer();
}

float Player::getTime()
{
	return playerWatch.elapsed_time();
}

void Player::stopWatch()
{
	playerWatch.stop_timer();
}

bool Player::isReverseBtnPressed() const
{
	return reverseBtnPressed;
}

void Player::resetReverseBtnPress()
{
	reverseBtnPressed = false;
}

PlayerRegion Player::get_bailey_region() const
{
	return player_region;
}

float Player::rightBoundary() const
{
	return right_boundary;
}

float Player::leftBoundary() const
{
	return left_boundary;
}

std::tuple<vector2f, vector2f> Player::distanceToDoor(shared_ptr<Igloo>& igloo)
{
	vector2f doorPosition = igloo->getDoorPosition();
	vector2f playerPos = position;
	vector2f _distanceToDoor;
	_distanceToDoor.x = abs(playerPos.x - doorPosition.x);
	_distanceToDoor.y = abs(playerPos.y - doorPosition.y);
	return { _distanceToDoor, doorPosition };
}

void Player::setPosition(const vector2f _position)
{
	position = _position;
	player_sprite.setPosition(position);
}