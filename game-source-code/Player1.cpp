#include "Player1.h"

Player1::Player1()
{
	player_texture.loadFromFile("resources/bailey.png");
}

void Player1::handleInput(bool keyPressed)
{
	auto state = getState();
	if (state != PlayerState::Alive)
	{
		return;
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::W) && !upPressed)
	{
		upPressed = true;
			
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::S) && !downPressed)
	{
		downPressed = true;
		//return;
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::A))
	{
		leftPressed = true;
		//return;
	}
	else
	{
		leftPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::D))
	{
		rightPressed = true;
		//return;
	}
	else
	{
		rightPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::LShift) && keyPressed &&
		(!reverseBtnPressed && !isPlayerInSafeZone()))
	{
		reverseBtnPressed = true;
	}	
}