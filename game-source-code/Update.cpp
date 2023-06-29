#include "Engine.h"

void Engine::update(const float dtAsSeconds)
{
	if (needToSpawn)
	{
		if (!splitScreen)
		{
			vector2f _pos;
			_pos.y = 199.0f;
			_pos.x = 224.0f;
			player1.spawnPlayer(_pos);
			needToSpawn = false;
		}
	}

	if (isPlaying)
	{
		if (!splitScreen)
		{
			//update single player mode
			player1.update(dtAsSeconds);
		}

		else
		{
			//update multiplayer mode (both players)
		}
	}
}