#include "Player1.h"

Player1::Player1()
{
	player_texture.loadFromFile("resources/bailey.png");
}

void Player1::handleInput()
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