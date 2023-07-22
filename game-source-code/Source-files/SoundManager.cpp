#include "../Header-files/SoundManager.h"

SoundManager::SoundManager()
{
	//load sound files in to buffers
	confirmationBuffer.loadFromFile("resources/confirm.wav");
	playerJumpBuffer.loadFromFile("resources/jump.wav");

	//load buffers in to sounds
	confirmationSound.setBuffer(confirmationBuffer);
	confirmationSound.setRelativeToListener(true);
	playerJumpSound.setBuffer(playerJumpBuffer);
	playerJumpSound.setRelativeToListener(true);
}

void SoundManager::playJumpingSound()
{
	playerJumpSound.play();
}

void SoundManager::playConfimationSound()
{
	confirmationSound.play();
}
