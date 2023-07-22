#include "../Header-files/SoundManager.h"

SoundManager::SoundManager()
{
	//load sound files in to buffers
	confirmationBuffer.loadFromFile("resources/confirm.wav");

	//load buffers in to sounds
	confirmationSound.setBuffer(confirmationBuffer);
	confirmationSound.setRelativeToListener(true);
}

void SoundManager::playConfimationSound()
{
	confirmationSound.play();
}
