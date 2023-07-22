#pragma once
#include <SFML/Audio.hpp>
#include "gameConstants.h"

class SoundManager
{
public:
	SoundManager();
	void playConfimationSound();
	void playJumpingSound();
	void playDeathSound();
	void playEatFishSound();

private:
	sf::SoundBuffer confirmationBuffer;
	sf::SoundBuffer playerJumpBuffer;
	sf::SoundBuffer playerDeathBuffer;
	sf::SoundBuffer eatFishBuffer;

	sf::Sound confirmationSound;
	sf::Sound playerJumpSound;
	sf::Sound playerDeathSound;
	sf::Sound eatFishSound;

};