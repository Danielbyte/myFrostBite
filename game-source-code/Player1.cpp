#include "Player1.h"

Player1::Player1()
{
	player_texture.loadFromFile("resources/bailey.png");
}

void Player1::handleInput()
{
	if (sf::Keyboard::isKeyPressed(Keyboard::Up))
	{
		//Logic for jumping up
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::Down))
	{
		//Logic for jumping down
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