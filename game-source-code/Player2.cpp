#include "Player2.h"

Player2::Player2()
{
	player_texture.loadFromFile("resources/bailey.png");
}

void Player2::handleInput()
{
	if (sf::Keyboard::isKeyPressed(Keyboard::Up))
	{
		upPressed = true;
	}
	else
	{
		upPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::Down))
	{
		downPressed = true;
	}
	else
	{
		downPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::Left))
	{
		leftPressed = true;
	}
	else
	{
		leftPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::Right))
	{
		rightPressed = true;
	}
	else
	{
		rightPressed = false;
	}
}