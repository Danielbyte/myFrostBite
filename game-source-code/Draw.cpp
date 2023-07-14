#include "Engine.h"

void Engine::display_manager(float dt)
{
	//Draw main menu
	if (!inMainMenu)
	{
		//Display other respective views if not in main menu
		if (!splitScreen)
		{
			//single player mode
			window->setView(singlePlayerView);
			auto player_state = player1.getState();
			if (player_state == PlayerState::Dead)
			{
				window->draw(game_over_sprite);
				window->display();
				return;
			}

			draw(crabs, clamps, birds, fish, igloo_house, bear, iceblocks, player1, overworld);
			/*
			auto inSafeZone = player1.isPlayerInSafeZone();
			auto isJumping = player1.isPlayerJumping();
			//auto isKilledByAnimal = player1.isPlayerKilledByAnimal();
			//auto isKilledByBear = player1.isKilledByBear();
			//auto iglooComplete = igloo_house->isComplete();
			auto [playerDistanceToDoor, IglooDoorPos] = player1.distanceToDoor(igloo_house);
			//auto isTimeUp = overworld.isTimeUp();
			//auto isDead = player1.getIfDead();


			if (player1Win)
			{
				window->draw(victory_sprite);
				window->display();
				return;
			}

			if (isTimeUp)
			{
				auto isAnimating = true;
				auto lives = player1.getNumberOfLives();
				Stopwatch s_watch;
				while (isAnimating)
				{
					auto TimeElapsed = s_watch.elapsed_time();
					animate.freezing_animation(TimeElapsed, player1);
					draw(crabs, clamps, birds, fish, igloo_house, bear, iceblocks, player1, overworld);
					window->display();
					
					if (TimeElapsed >= 1.1f)
					{
						isAnimating = false;
					}
				}
				player1.subractLive();
				player1.set_state();
				if (lives > 0)
				{
					player1.spawnPlayer();
					bear->spawnBear();
					overworld.resetTemperature();
					iceblocks.clear();
					canCreateIce = true;
					clamps.clear();
					birds.clear();
					crabs.clear();
				}
			}

			if (inSafeZone && iglooComplete && playerDistanceToDoor.x <= 35.0f)
			{
				Stopwatch s_watch;
				bool isInside = false;
				while (!isInside)
				{
					auto [playerDistanceToDoor, iglooDoorPos] = player1.distanceToDoor(igloo_house);
					auto TimeElapsed = s_watch.elapsed_time();
					vector2f playerPos = player1.getPosition();
					float goingInIgloo_X_speed = 100.0f;
					float goingInIgloo_Y_speed = 9.5f;
					auto igloorDoorOffset = 14.5f;
					if (playerPos.x > iglooDoorPos.x)
					{
						if (playerDistanceToDoor.x > 1.0f)
						{
							vector2f pos = player1.getPosition();
							pos.x -= TimeElapsed * goingInIgloo_X_speed;
							player1.setPosition(pos);
						}
					}

					if (playerPos.x < iglooDoorPos.x)
					{
						if (playerDistanceToDoor.x > igloorDoorOffset)
						{
							vector2f pos = player1.getPosition();
							pos.x += TimeElapsed * goingInIgloo_X_speed;
							player1.setPosition(pos);
						}
					}

					if (playerPos.y > iglooDoorPos.y)
					{
						vector2f pos = player1.getPosition();
						pos.y -= TimeElapsed * goingInIgloo_Y_speed;
						player1.setPosition(pos);
					}

					animate.go_inside_igloo(playerPos.y, player1);
					draw(crabs, clamps, birds, fish, igloo_house, bear, iceblocks, player1, overworld);
					window->display();

					if (playerPos.y < 133.0f)
					{
						isInside = true;
						//is_playing = false;
						//is_game_over = true;
						window->setKeyRepeatEnabled(false);
					}
				}
				player1Win = true;
			}

			if (!inSafeZone && !isJumping)
			{
				auto isDrowning = player1.isPlayerDrowning();
				if (isDrowning)
				{
					auto isAnimating = true;
					Stopwatch s_watch;
					auto lives = player1.getNumberOfLives();

					while (isAnimating)
					{
						auto TimeElapsed = s_watch.elapsed_time();
						animate.drowning_player(TimeElapsed, player1);
						draw(crabs, clamps, birds, fish, igloo_house, bear, iceblocks, player1, overworld);
						window->display();

						if (TimeElapsed >= 1.03f)
						{
							isAnimating = false;
						}
					}
					player1.subractLive();
					player1.set_state();

					if (lives > 0)
					{
						player1.ressurectFromDrownDeath();
						player1.spawnPlayer();
						bear->spawnBear();
						iceblocks.clear();
						canCreateIce = true;
						clamps.clear();
						birds.clear();
						crabs.clear();
					}
				}
			}

			if (isKilledByAnimal)
			{
				auto isAnimating = true;
				Stopwatch s_watch;
				auto lives = player1.getNumberOfLives();

				while (isAnimating)
				{
					auto TimeElapsed = s_watch.elapsed_time();
					animate.collision_with_sea_animal(TimeElapsed, player1);
					draw(crabs, clamps, birds, fish, igloo_house, bear, iceblocks, player1, overworld);
					window->display();

					if (TimeElapsed >= 1.03f)
					{
						isAnimating = false;
					}
				}

				if (lives > 0)
				{
					player1.spawnPlayer();
					player1.ressurectFromAnimalDeath();
					bear->spawnBear();
					iceblocks.clear();
					canCreateIce = true;
					clamps.clear();
					birds.clear();
					crabs.clear();
				}
			}

			if (isKilledByBear)
			{
				auto isAnimating = true;
				Stopwatch s_watch;
				auto lives = player1.getNumberOfLives();
				
				while (isAnimating)
				{
					auto TimeElapsed = s_watch.elapsed_time();
					animate.killed_by_bear(TimeElapsed, player1);
					draw(crabs, clamps, birds, fish, igloo_house, bear, iceblocks, player1, overworld);
					window->display();
		
					if (TimeElapsed >= 1.03f)
					{
						isAnimating = false;
					}
				}

				if (lives > 0)
				{
					player1.spawnPlayer();
					player1.ressurectFromBearDeath();
					bear->spawnBear();
					iceblocks.clear();
					canCreateIce = true;
					clamps.clear();
					birds.clear();
					crabs.clear();
				}
			}
			*/
		}
		else
		{
			/*
			//multiplayer mode
			//player1 side
			window->setView(LeftViewB);
			window->draw(background_sprite);
			window->setView(leftView);
			draw(crabs, clamps, birds, fish, igloo_house, bear, iceblocks, player1, overworld);

			auto inSafeZone = player1.isPlayerInSafeZone();
			auto isJumping = player1.isPlayerJumping();
			auto isKilledByAnimal = player1.isPlayerKilledByAnimal();
			auto isKilledByBear = player1.isKilledByBear();
			auto iglooComplete = igloo_house->isComplete();
			auto [playerDistanceToDoor, IglooDoorPos] = player1.distanceToDoor(igloo_house);
			auto isTimeUp = overworld.isTimeUp();
			auto isDead = player1.getIfDead();

			if (isDead || player1Win)
			{
				window->setView(leftView);
				window->draw(background_sprite);

				if (isDead)
				{
					window->draw(game_over_sprite);
				}

				if (player1Win)
				{
					window->draw(victory_sprite);
				}
			}

			else
			{
				if (isTimeUp)
				{
					auto isAnimating = true;
					auto lives = player1.getNumberOfLives();
					Stopwatch s_watch;
					while (isAnimating)
					{
						auto TimeElapsed = s_watch.elapsed_time();
						animate.freezing_animation(TimeElapsed, player1);
						World1Animations(dt, TimeElapsed, isAnimating, freezeAnimDur);
					}
					player1.subractLive();
					player1.set_state();
					if (lives > 0)
					{
						player1.spawnPlayer();
						bear->spawnBear();
						overworld.resetTemperature();
						iceblocks.clear();
						canCreateIce = true;
						clamps.clear();
						birds.clear();
						crabs.clear();
					}
				}

				if (!inSafeZone && !isJumping)
				{
					auto isDrowning = player1.isPlayerDrowning();
					if (isDrowning)
					{
						auto lives = player1.getNumberOfLives();
						auto isAnimating = true;
						Stopwatch s_watch;
					
						while (isAnimating)
						{
							auto TimeElapsed = s_watch.elapsed_time();
							animate.drowning_player(TimeElapsed, player1);
							World1Animations(dt, TimeElapsed, isAnimating, standardAnimDur);
						}

						player1.subractLive();
						player1.set_state();
						fromOverWorld1Animation = true;

						if (lives > 0)
						{
							player1.spawnPlayer();
							player1.ressurectFromDrownDeath();
							bear->spawnBear();
							iceblocks.clear();
							canCreateIce = true;
							clamps.clear();
							birds.clear();
							crabs.clear();
						}

					}
				}

				if (isKilledByAnimal)
				{
					auto lives = player1.getNumberOfLives();
					auto isAnimating = true;
					Stopwatch s_watch;

					while (isAnimating)
					{
						auto TimeElapsed = s_watch.elapsed_time();
						animate.collision_with_sea_animal(TimeElapsed, player1);
						World1Animations(dt, TimeElapsed, isAnimating, standardAnimDur);
					}

					player1.subractLive();
					player1.set_state();
					fromOverWorld1Animation = true;

					if (lives > 0)
					{
						player1.spawnPlayer();
						player1.ressurectFromAnimalDeath();
						bear->spawnBear();
						iceblocks.clear();
						canCreateIce = true;
						clamps.clear();
						birds.clear();
						crabs.clear();
					}

				}

				if (isKilledByBear)
				{
					auto isAnimating = true;
					Stopwatch s_watch;
					auto lives = player1.getNumberOfLives();

					while (isAnimating)
					{
						auto TimeElapsed = s_watch.elapsed_time();
						animate.killed_by_bear(TimeElapsed, player1);
						World1Animations(dt, TimeElapsed, isAnimating, standardAnimDur);
					}

					player1.subractLive();
					player1.set_state();
					fromOverWorld1Animation = true;

					if (lives > 0)
					{
						player1.spawnPlayer();
						player1.ressurectFromBearDeath();
						bear->spawnBear();
						iceblocks.clear();
						canCreateIce = true;
						clamps.clear();
						birds.clear();
						crabs.clear();
					}
				}

				if (inSafeZone && iglooComplete && playerDistanceToDoor.x <= 35.0f)
				{
					Stopwatch s_watch;
					bool isInside = false;
					while (!isInside)
					{
						auto [playerDistanceToDoor, iglooDoorPos] = player1.distanceToDoor(igloo_house);
						auto TimeElapsed = s_watch.elapsed_time();
						vector2f playerPos = player1.getPosition();
						float goingInIgloo_X_speed = 100.0f;
						float goingInIgloo_Y_speed = 9.5f;
						auto igloorDoorOffset = 14.5f;
						if (playerPos.x > iglooDoorPos.x)
						{
							if (playerDistanceToDoor.x > 1.0f)
							{
								vector2f pos = player1.getPosition();
								pos.x -= TimeElapsed * goingInIgloo_X_speed;
								player1.setPosition(pos);
							}
						}

						if (playerPos.x < iglooDoorPos.x)
						{
							if (playerDistanceToDoor.x > igloorDoorOffset)
							{
								vector2f pos = player1.getPosition();
								pos.x += TimeElapsed * goingInIgloo_X_speed;
								player1.setPosition(pos);
							}
						}

						if (playerPos.y > iglooDoorPos.y)
						{
							vector2f pos = player1.getPosition();
							pos.y -= TimeElapsed * goingInIgloo_Y_speed;
							player1.setPosition(pos);
						}

						animate.go_inside_igloo(playerPos.y, player1);
						draw(crabs, clamps, birds, fish, igloo_house, bear, iceblocks, player1, overworld);
						window->display();

						if (playerPos.y < 133.0f)
						{
							isInside = true;
							//is_playing = false;
							//is_game_over = true;
							window->setKeyRepeatEnabled(false);
						}
					}
					player1Win = true;
				}
			}
			//Draw line that separates two screens
			window->draw(line_sprite);
			
			//player2 side
			window->setView(RightViewB);
			window->draw(background_sprite);
			window->setView(rightView);
			draw(crabs2, clamps2, birds2, fish2, igloo_house2, bear2, iceblocks2, player2, overworld2);

			inSafeZone = player2.isPlayerInSafeZone();
			isJumping = player2.isPlayerJumping();
			isKilledByAnimal = player2.isPlayerKilledByAnimal();
			isKilledByBear = player2.isKilledByBear();
			iglooComplete = igloo_house2->isComplete();
			auto [playerDistanceToDoor2, IglooDoorPos2] = player2.distanceToDoor(igloo_house2);
			isTimeUp = overworld2.isTimeUp();
			isDead = player2.getIfDead();

			if (isDead || player2Win)
			{
				window->setView(rightView);
				window->draw(background_sprite);

				if (isDead)
				{
					window->draw(game_over_sprite);
				}

				if (player2Win)
				{
					window->draw(victory_sprite);
				}
			}

			else
			{
				if (isTimeUp)
				{
					auto isAnimating = true;
					auto lives = player2.getNumberOfLives();
					Stopwatch s_watch;
					while (isAnimating)
					{
						auto TimeElapsed = s_watch.elapsed_time();
						animate.freezing_animation(TimeElapsed, player2);
						World2Animations(dt, TimeElapsed, isAnimating, freezeAnimDur);
					}
					player2.subractLive();
					player2.set_state();
					if (lives > 0)
					{
						player2.spawnPlayer();
						bear2->spawnBear();
						overworld2.resetTemperature();
						iceblocks2.clear();
						canCreateIce2 = true;
						clamps2.clear();
						birds2.clear();
						crabs2.clear();
					}
				}

				if (!inSafeZone && !isJumping)
				{
					auto isDrowning = player2.isPlayerDrowning();
					if (isDrowning)
					{
						auto lives = player2.getNumberOfLives();
						auto isAnimating = true;
						Stopwatch s_watch;

						while (isAnimating)
						{
							auto TimeElapsed = s_watch.elapsed_time();
							animate.drowning_player(TimeElapsed, player2);
							World2Animations(dt, TimeElapsed, isAnimating, standardAnimDur);
						}

						player2.subractLive();
						player2.set_state();
						fromOverWorld2Animation = true;

						if (lives > 0)
						{
							player2.spawnPlayer();
							player2.ressurectFromDrownDeath();
							bear2->spawnBear();
							iceblocks2.clear();
							canCreateIce2 = true;
							clamps2.clear();
							birds2.clear();
							crabs2.clear();
						}

					}
				}

				if (isKilledByAnimal)
				{
					auto lives = player2.getNumberOfLives();
					auto isAnimating = true;
					Stopwatch s_watch;
					while (isAnimating)
					{
						auto TimeElapsed = s_watch.elapsed_time();
						animate.collision_with_sea_animal(TimeElapsed, player2);
						World2Animations(dt, TimeElapsed, isAnimating,standardAnimDur);
					}

					player2.subractLive();
					player2.set_state();
					fromOverWorld2Animation = true;

					if (lives > 0)
					{
						player2.spawnPlayer();
						player2.ressurectFromAnimalDeath();
						bear2->spawnBear();
						iceblocks2.clear();
						canCreateIce2 = true;
						clamps2.clear();
						birds2.clear();
						crabs2.clear();
					}
				}

				if (isKilledByBear)
				{
					auto isAnimating = true;
					Stopwatch s_watch;
					auto lives = player2.getNumberOfLives();

					while (isAnimating)
					{
						auto TimeElapsed = s_watch.elapsed_time();
						animate.killed_by_bear(TimeElapsed, player2);
						World2Animations(dt, TimeElapsed, isAnimating, standardAnimDur);
					}

					player2.subractLive();
					player2.set_state();
					fromOverWorld2Animation = true;

					if (lives > 0)
					{
						player2.spawnPlayer();
						player2.ressurectFromBearDeath();
						bear2->spawnBear();
						iceblocks2.clear();
						canCreateIce2 = true;
						clamps2.clear();
						birds2.clear();
						crabs2.clear();
					}
				}

				if (inSafeZone && iglooComplete && playerDistanceToDoor2.x <= 35.0f)
				{
					Stopwatch s_watch;
					bool isInside = false;
					while (!isInside)
					{
						auto [playerDistanceToDoor2, iglooDoorPos2] = player2.distanceToDoor(igloo_house2);
						auto TimeElapsed = s_watch.elapsed_time();
						vector2f playerPos = player2.getPosition();
						float goingInIgloo_X_speed = 100.0f;
						float goingInIgloo_Y_speed = 9.5f;
						auto igloorDoorOffset = 14.5f;
						if (playerPos.x > iglooDoorPos2.x)
						{
							if (playerDistanceToDoor2.x > 1.0f)
							{
								vector2f pos = player2.getPosition();
								pos.x -= TimeElapsed * goingInIgloo_X_speed;
								player2.setPosition(pos);
							}
						}

						if (playerPos.x < iglooDoorPos2.x)
						{
							if (playerDistanceToDoor2.x > igloorDoorOffset)
							{
								vector2f pos = player2.getPosition();
								pos.x += TimeElapsed * goingInIgloo_X_speed;
								player2.setPosition(pos);
							}
						}

						if (playerPos.y > iglooDoorPos2.y)
						{
							vector2f pos = player2.getPosition();
							pos.y -= TimeElapsed * goingInIgloo_Y_speed;
							player2.setPosition(pos);
						}

						animate.go_inside_igloo(playerPos.y, player2);
						draw(crabs2, clamps2, birds2, fish2, igloo_house2, bear2, iceblocks2, player2, overworld2);
						window->display();
					
						if (playerPos.y < 133.0f)
						{
							isInside = true;
							//is_playing = false;
							//is_game_over = true;
							window->setKeyRepeatEnabled(false);
						}
					}

					player2Win = true;
				}
			}
			*/
		}
	}

	else
	{
		//Draw main menu view
		window->setView(MainmenuView);
		window->draw(menu_sprite);
		window->draw(menu.getCursor());
	}

	window->display();
}

void Engine::draw(vector<shared_ptr<Crab>>& _crabs, vector<shared_ptr<Clamp>>& _clamps,
	vector<shared_ptr<Bird>>& _birds,vector<shared_ptr<Fish>>& _fish, shared_ptr<Igloo>& iglooHouse,
	shared_ptr<Bear>& _bear, vector<shared_ptr<IceBlocks>>& _ice, Player& _player, OverWorld& _overworld)
{
	window->draw(background_sprite);
	//Draw birds
	draw_overWorld(_birds);
	//Draw crabs
	draw_overWorld(_crabs);
	//Draw clamps
	draw_overWorld(_clamps);
	//Draw fish
	draw_overWorld(_fish);
	//Draw ice
	draw_overWorld(_ice);
	window->draw(iglooHouse->getSprite());
	window->draw(_bear->getSprite());
	window->draw(_overworld.getTemperature());
	window->draw(_overworld.getTemperatureSymbol());
	window->draw(_player.getSprite());
}

void Engine::World1Animations(const float _dt, const float TimeElapsed, bool& isAnimating, float duration)
{
	window->setView(leftView);
	window->draw(background_sprite);
	draw(crabs, clamps, birds, fish, igloo_house, bear, iceblocks, player1, overworld);
	window->draw(line_sprite);

	window->setView(rightView);
	auto isDead = player2.getIfDead();

	if (!isDead && !player2Win)
	{
		window->draw(background_sprite);
		handleInput();
		updatePlayer2World(_dt);
		draw(crabs2, clamps2, birds2, fish2, igloo_house2, bear2, iceblocks2, player2, overworld2);
	}

	if (TimeElapsed >= duration)
	{
		isAnimating = false;
	}

	window->display();
}

void Engine::World2Animations(const float _dt, const float TimeElapsed, bool& isAnimating, float duration)
{
	window->setView(rightView);
	window->draw(background_sprite);
	draw(crabs2, clamps2, birds2, fish2, igloo_house2, bear2, iceblocks2, player2, overworld2);

	window->setView(leftView);

	auto isDead = player1.getIfDead();
	if (!player1Win && !isDead)
	{
		window->draw(background_sprite);
		handleInput();
		//updatePlayer
		draw(crabs, clamps, birds, fish, igloo_house, bear, iceblocks, player1, overworld);
	}

	window->draw(line_sprite);

	if (TimeElapsed >= duration)
	{
		isAnimating = false;
	}

	window->display();
}