#include "../Header-files/Engine.h"

void Engine::update(float dtAsSeconds)
{
    if (reInitialise)
    {
        resetGame();
        return;
    }

	if (isPlaying)
	{
		if (needToSpawn) // initially spawn players
		{
			if (!splitScreen)
			{
				//single player mode
				player1->spawnPlayer();
				needToSpawn = false;
			}

			else
			{
				//multiplayer mode
				player1->spawnPlayer();
				player2->spawnPlayer();
				needToSpawn = false;
			}
		}

		if (!splitScreen)
		{
			//update single player mode
            updateGamePlay(dtAsSeconds, player1, crabs, clamps, birds, fish, overworld, bear, igloo_house,
                iceblocks, overworld_watch, canCreateIce);
		}

		else
		{
			//update multiplayer mode (both players)
            //update player 1 side
            updateGamePlay(dtAsSeconds, player1, crabs, clamps, birds, fish, overworld, bear, igloo_house,
                iceblocks, overworld_watch, canCreateIce);

           // update player 2 side
            updateGamePlay(dtAsSeconds, player2, crabs2, clamps2, birds2, fish2, overworld2, bear2, igloo_house2,
                iceblocks2, overworld_watch2, canCreateIce2);
		}
	}
}

void Engine::update_over_world(const float deltaTime,OverWorld& _overworld, 
    vector<shared_ptr<Crab>>& _crabs,vector<shared_ptr<Clamp>>& _clamps, vector<shared_ptr<Bird>>& _birds,
    vector<shared_ptr<Fish>>& _fish,vector<shared_ptr<IceBlocks>>& _ice, Stopwatch& _overworld_watch,
    shared_ptr<Player>& _player)
{
    //create enemy every 5 seconds
    auto timeElapsed = _overworld_watch.elapsed_time();

    if (timeElapsed >= 5)
    {
        auto isEnemyInRegion1 = _overworld.Isanimal_in_region1();
        auto isEnemyInRegion2 = _overworld.Isanimal_in_region2();
        auto isEnemyInRegion3 = _overworld.Isanimal_in_region3();
        auto isEnemyInRegion4 = _overworld.Isanimal_in_region4();

        //Create enemies if there are none at respective regions
        if (!isEnemyInRegion1)
        {
            //Create any enemy in region 1
            auto r1Pos = _overworld.getRegion1Position();
            _overworld.create_animal(_crabs, _clamps, _birds, _fish, r1Pos);
        }

        if (!isEnemyInRegion2)
        {
            //create enemy in region 2
            auto r2Pos = _overworld.getRegion2Position();
            _overworld.create_animal(_crabs, _clamps, _birds, _fish, r2Pos);
        }

        if (!isEnemyInRegion3)
        {
            //create any enemy in region 3
            auto r3Pos = _overworld.getRegion3Position();
            _overworld.create_animal(_crabs, _clamps, _birds, _fish, r3Pos);
        }

        if (!isEnemyInRegion4)
        {
            //create any enemy in region 4
            auto r4Pos = _overworld.getRegion4Position();
            _overworld.create_animal(_crabs, _clamps, _birds, _fish, r4Pos);
        }
        _overworld_watch.restart_timer();
    }

    control_crabs->update_crab(_crabs, deltaTime);
    control_clamps->update_clamp(_clamps, deltaTime);
    control_fish->update_fish(_fish, deltaTime);
    control_birds->update_birds(_birds, deltaTime);

    _overworld.update_animals_in_regions(_crabs, _clamps, _birds, _fish);

    if (canCreateIce)
    {
        canCreateIce = false;
        _overworld.create_ice(iceblocks);
    }
    if (canCreateIce2)
    {
        canCreateIce2 = false;
        _overworld.create_ice(iceblocks2);
    }
    control_ice->update_iceblocks(_ice, deltaTime);
    control_ice->update_ice_texture(_ice);
    _overworld.update_temperature(_player, manage_sound);
}

void Engine::updateGamePlay(float dtAsSeconds, shared_ptr<Player>& _player, vector<shared_ptr<Crab>>& _crabs,
    vector<shared_ptr<Clamp>>& _clamps, vector<shared_ptr<Bird>>& _birds, vector<shared_ptr<Fish>>& _fish,
    OverWorld& _overworld, shared_ptr<Bear>& _bear, shared_ptr<Igloo>& _igloo, 
    vector<shared_ptr<IceBlocks>>& _ice, Stopwatch& _overWorldWatch, bool& _canCreateIce)
{
    auto player_state = _player->getState();
    if (player_state != PlayerState::Alive)
    {
        animate.animateAndSetState(_player, _crabs, _clamps, _birds, _bear, _ice, _canCreateIce, _overworld,
            _igloo);
        return;
    }

    //avoid glitches in game frame
    if (dtAsSeconds >= 1) { dtAsSeconds = standard_dt; }

    _player->update(dtAsSeconds, manage_sound);
    _player->updateHUDSprite();
    update_over_world(dtAsSeconds, _overworld, _crabs, _clamps, _birds, _fish, _ice, _overWorldWatch, _player);
    _bear->update_bear(dtAsSeconds, _player);
    manage_collisions.player_ice_collisions(_player, _ice, dtAsSeconds, _igloo, manage_sound);
    manage_collisions.player_animal_collisions(_player, _crabs, _clamps, _birds, _fish, manage_sound);
    manage_collisions.player_bear_collisions(_bear, _player, manage_sound);
    animate.animateAndSetState(_player,_crabs,_clamps,_birds,_bear,_ice,_canCreateIce,_overworld,_igloo);
    _igloo->update_igloo();
}