#include "Engine.h"

void Engine::update(float dtAsSeconds)
{
	if (isPlaying)
	{
		if (needToSpawn) // initially spawn players
		{
			if (!splitScreen)
			{
				//single player mode
				player1.spawnPlayer();
				needToSpawn = false;
			}

			else
			{
				//multiplayer mode
				player1.spawnPlayer();
				player2.spawnPlayer();
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
            //updatePlayer1World(dtAsSeconds);
           // updatePlayer2World(dtAsSeconds);
		}
	}
}

void Engine::update_over_world(const float deltaTime, OverWorld& _overworld, vector<shared_ptr<Crab>>& _crabs,
    vector<shared_ptr<Clamp>>& _clamps, vector<shared_ptr<Bird>>& _birds, vector<shared_ptr<Fish>>& _fish,
    vector<shared_ptr<IceBlocks>>& _ice, Stopwatch& _overworld_watch, Player& _player)
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
            overworld.create_animal(_crabs, _clamps, _birds, _fish, r3Pos);
        }

        if (!isEnemyInRegion4)
        {
            //create any enemy in region 4
            auto r4Pos = _overworld.getRegion4Position();
            _overworld.create_animal(_crabs, _clamps, _birds, _fish, r4Pos);
        }
        _overworld_watch.restart_timer();
    }

    control_crabs.update_crab(_crabs, deltaTime);
    control_clamps.update_clamp(_clamps, deltaTime);
    control_fish.update_fish(_fish, deltaTime);
    control_birds.update_birds(_birds, deltaTime);

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
    control_ice.update_iceblocks(_ice, deltaTime);
    control_ice.update_ice_texture(_ice);
    _overworld.update_temperature(_player);
}

void Engine::updatePlayer2World(float dtAsSeconds)
{
    //Since game entities update wrt time, the code below helps keep 
    //the time constant (after animations in world1) for smoother game play.
    if (fromOverWorld1Animation)
    {
        dtAsSeconds = standard_dt;
        fromOverWorld1Animation = false;
    }

    if (dtAsSeconds >= 1) { dtAsSeconds = standard_dt; }

    player2.update(dtAsSeconds);
    update_over_world(dtAsSeconds, overworld2, crabs2, clamps2, birds2, fish2, iceblocks2, overworld_watch2, player2);
    animate.animate_player(player2);
    bear2->update_bear(dtAsSeconds, player2);
    manage_collisions.player_ice_collisions(player2, iceblocks2, dtAsSeconds, igloo_house2);
    manage_collisions.player_animal_collisions(player2, crabs2, clamps2, birds2, fish2);
    manage_collisions.player_bear_collisions(bear2, player2);
    igloo_house2->update_igloo();
}

void Engine::updateGamePlay(float dtAsSeconds, Player& _player, vector<shared_ptr<Crab>>& _crabs,
    vector<shared_ptr<Clamp>>& _clamps, vector<shared_ptr<Bird>>& _birds, vector<shared_ptr<Fish>>& _fish,
    OverWorld& _overworld, shared_ptr<Bear>& _bear, shared_ptr<Igloo>& _igloo, 
    vector<shared_ptr<IceBlocks>>& _ice, Stopwatch& _overWorldWatch, bool& _canCreateIce)
{
    //Since game entities update wrt time, the code below helps keep 
    //the time constant (after animations in world2) for smoother game play.
    auto player_state = _player.getState();
    if (player_state != PlayerState::Alive)
    {
        animate.animate(_player, _crabs, _clamps, _birds, _bear, _ice, _canCreateIce, _overworld);
        return;
    }

    if (dtAsSeconds >= 1) { dtAsSeconds = standard_dt; }

    _player.update(dtAsSeconds);
    update_over_world(dtAsSeconds, _overworld, _crabs, _clamps, _birds, _fish, _ice, _overWorldWatch, _player);
    _bear->update_bear(dtAsSeconds, _player);
    manage_collisions.player_ice_collisions(_player, _ice, dtAsSeconds, _igloo);
    manage_collisions.player_animal_collisions(_player, _crabs, _clamps, _birds, _fish);
   // manage_collisions.player_bear_collisions(_bear, _player);
    animate.animate(_player,_crabs,_clamps,_birds,_bear,_ice,_canCreateIce,_overworld);
    _igloo->update_igloo();
}