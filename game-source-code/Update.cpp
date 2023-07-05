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
            update_over_world(dtAsSeconds);
		}

		else
		{
			//update multiplayer mode (both players)
			player1.update(dtAsSeconds);
			player2.update(dtAsSeconds);
            update_over_world(dtAsSeconds);
		}
	}
}

void Engine::update_over_world(const float deltaTime)
{
    //create enemy every 5 seconds
    auto timeElapsed = overworld_watch.elapsed_time();

    if (timeElapsed >= 5)
    {
        auto isEnemyInRegion1 = overworld.Isanimal_in_region1();
        auto isEnemyInRegion2 = overworld.Isanimal_in_region2();
        auto isEnemyInRegion3 = overworld.Isanimal_in_region3();
        auto isEnemyInRegion4 = overworld.Isanimal_in_region4();

        //Create enemies if there are none at respective regions
        if (!isEnemyInRegion1)
        {
            //Create any enemy in region 1
            auto r1Pos = overworld.getRegion1Position();
            overworld.create_animal(crabs, clamps, birds, fish, r1Pos);
        }

        if (!isEnemyInRegion2)
        {
            //create enemy in region 2
            auto r2Pos = overworld.getRegion2Position();
            overworld.create_animal(crabs, clamps, birds, fish, r2Pos);
        }

        if (!isEnemyInRegion3)
        {
            //create any enemy in region 3
            auto r3Pos = overworld.getRegion3Position();
            overworld.create_animal(crabs, clamps, birds, fish, r3Pos);
        }

        if (!isEnemyInRegion4)
        {
            //create any enemy in region 4
            auto r4Pos = overworld.getRegion4Position();
            overworld.create_animal(crabs, clamps, birds, fish, r4Pos);
        }
        overworld_watch.restart_timer();
    }

    control_crabs.update_crab(crabs, deltaTime);
    control_clamps.update_clamp(clamps, deltaTime);
    control_fish.update_fish(fish, deltaTime);
    control_birds.update_birds(birds, deltaTime);

    overworld.update_animals_in_regions(crabs, clamps, birds, fish);
}