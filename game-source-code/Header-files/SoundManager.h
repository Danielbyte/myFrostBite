#pragma once
#include <SFML/Audio.hpp>

class SoundManager
{
public:
	SoundManager();
	void playConfimationSound();
	void playJumpingSound();
	void playDeathSound();
	void playEatFishSound();
	void playTemperatureScoreCountSound();
	void playIglooScoreCountSound();

private:
	sf::SoundBuffer confirmationBuffer;
	sf::SoundBuffer playerJumpBuffer;
	sf::SoundBuffer playerDeathBuffer;
	sf::SoundBuffer eatFishBuffer;
	sf::SoundBuffer temperatureScoreCountBuffer;
	sf::SoundBuffer iglooScoreCountBuffer;

	sf::Sound confirmationSound;
	sf::Sound playerJumpSound;
	sf::Sound playerDeathSound;
	sf::Sound eatFishSound;
	sf::Sound temperatureScoreCountSound;
	sf::Sound iglooScoreCountSound;
};