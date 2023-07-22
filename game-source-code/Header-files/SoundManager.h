#pragma once
#include <SFML/Audio.hpp>

class SoundManager
{
public:
	SoundManager();
	void playConfimationSound();

private:
	sf::SoundBuffer confirmationBuffer;

	sf::Sound confirmationSound;

};