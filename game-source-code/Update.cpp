#include "Engine.h"

void Engine::update(const float dtAsSeconds)
{
	if (isPlaying)
	{
		if (needToSpawn) // initially spawn players
		{
			if (!splitScreen)
			{
				//single player mode
				vector2f _pos;
				_pos.y = 199.0f;
				_pos.x = 224.0f;
				player1.spawnPlayer(_pos);
				needToSpawn = false;
			}

			else
			{
				//multiplayer mode
				vector2f _pos;
				_pos.y = 199.0f;
				_pos.x = 224.0f;
				player1.spawnPlayer(_pos);
				player2.spawnPlayer(_pos);
				needToSpawn = false;
			}
		}

		if (!splitScreen)
		{
			//update single player mode
			player1.update(dtAsSeconds);
		}

		else
		{
			//update multiplayer mode (both players)
			player1.update(dtAsSeconds);
			player2.update(dtAsSeconds);
		}
	}
}