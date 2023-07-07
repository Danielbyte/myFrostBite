#include "Player1.h"

Player1::Player1()
{
	player_texture.loadFromFile("resources/bailey.png");
}

void Player1::handleInput()
{
	if (sf::Keyboard::isKeyPressed(Keyboard::W) && !upPressed)
	{
		upPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::S) && !downPressed)
	{
		downPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::A))
	{
		leftPressed = true;
	}
	else
	{
		leftPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::D))
	{
		rightPressed = true;
	}
	else
	{
		rightPressed = false;
	}
}