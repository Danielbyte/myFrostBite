#include "../Header-files/Player2.h"

Player2::Player2()
{
	player_texture.loadFromFile("resources/bailey.png");
}

void Player2::handleInput(bool keyPressed)
{
	auto state = getState();
	if (state != PlayerState::Alive)
	{
		return;
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::Up) && !upPressed)
	{
		upPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::Down) && !downPressed)
	{
		downPressed = true;
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

	if (sf::Keyboard::isKeyPressed(Keyboard::Space) && keyPressed &&
		(!reverseBtnPressed && !playerInSafeZone))
	{
		reverseBtnPressed = true;
	}
}