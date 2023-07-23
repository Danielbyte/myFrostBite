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
	void playMoveInSound();

private:
	sf::SoundBuffer confirmationBuffer;
	sf::SoundBuffer playerJumpBuffer;
	sf::SoundBuffer playerDeathBuffer;
	sf::SoundBuffer eatFishBuffer;
	sf::SoundBuffer temperatureScoreCountBuffer;
	sf::SoundBuffer iglooScoreCountBuffer;
	sf::SoundBuffer playerMoveInBuffer;

	sf::Sound confirmationSound;
	sf::Sound playerJumpSound;
	sf::Sound playerDeathSound;
	sf::Sound eatFishSound;
	sf::Sound temperatureScoreCountSound;
	sf::Sound iglooScoreCountSound;
	sf::Sound playerMoveInSound;
};