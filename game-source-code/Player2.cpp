#include "Player2.h"

Player2::Player2()
{
	player_texture.loadFromFile("resources/bailey.png");
}

void Player2::handleInput()
{
	if (sf::Keyboard::isKeyPressed(Keyboard::W))
	{
		//Logic for jumping up
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::S))
	{
		//Logic for jumping down
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