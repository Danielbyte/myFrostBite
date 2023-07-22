#pragma once
#include <SFML/Audio.hpp>
#include "gameConstants.h"

class SoundManager
{
public:
	SoundManager();
	void playConfimationSound();
	void playJumpingSound();

private:
	sf::SoundBuffer confirmationBuffer;
	sf::SoundBuffer playerJumpBuffer;

	sf::Sound confirmationSound;
	sf::Sound playerJumpSound;

};