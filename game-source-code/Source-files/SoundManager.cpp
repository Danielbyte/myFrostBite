#include "../Header-files/SoundManager.h"

SoundManager::SoundManager()
{
	//load sound files in to buffers
	confirmationBuffer.loadFromFile("resources/confirm.wav");
	playerJumpBuffer.loadFromFile("resources/jump.wav");
	playerDeathBuffer.loadFromFile("resources/death.wav");
	eatFishBuffer.loadFromFile("resources/eatfish.wav");
	temperatureScoreCountBuffer.loadFromFile("resources/temperature_score.wav");
	iglooScoreCountBuffer.loadFromFile("resources/igloo_points.wav");

	//load buffers in to sounds
	confirmationSound.setBuffer(confirmationBuffer);
	confirmationSound.setRelativeToListener(true);
	playerJumpSound.setBuffer(playerJumpBuffer);
	playerJumpSound.setRelativeToListener(true);
	playerDeathSound.setBuffer(playerDeathBuffer);
	playerDeathSound.setRelativeToListener(true);
	eatFishSound.setBuffer(eatFishBuffer);
	eatFishSound.setRelativeToListener(true);
	temperatureScoreCountSound.setBuffer(temperatureScoreCountBuffer);
	temperatureScoreCountSound.setRelativeToListener(true);
	iglooScoreCountSound.setBuffer(iglooScoreCountBuffer);
	iglooScoreCountSound.setRelativeToListener(true);
}

void SoundManager::playIglooScoreCountSound()
{
	iglooScoreCountSound.play();
}

void SoundManager::playTemperatureScoreCountSound()
{
	temperatureScoreCountSound.play();
}

void SoundManager::playEatFishSound()
{
	eatFishSound.play();
}

void SoundManager::playJumpingSound()
{
	playerJumpSound.play();
}

void SoundManager::playDeathSound()
{
	playerDeathSound.play();
}

void SoundManager::playConfimationSound()
{
	confirmationSound.play();
}
