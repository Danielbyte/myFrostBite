#include "Engine.h"

void Engine::display_manager()
{
	window->clear(Color::White);
	//Draw main menu
	if (!inMainMenu)
	{
		//Display other respective views if not in main menu
		if (!splitScreen)
		{
			//single player mode
			window->setView(singlePlayerView);
			draw(crabs, clamps, birds, fish, igloo_house, bear, iceblocks, player1, overworld);

			auto inSafeZone = player1.isPlayerInSafeZone();
			auto isJumping = player1.isPlayerJumping();
			auto isKilledByAnimal = player1.isPlayerKilledByAnimal();
			auto isKilledByBear = player1.isKilledByBear();
			auto iglooComplete = igloo_house->isComplete();
			auto [playerDistanceToDoor, IglooDoorPos] = player1.distanceToDoor(igloo_house);
			auto isTimeUp = overworld.isTimeUp();
			auto isDead = player1.getIfDead();

			if (isDead)
			{
				window->clear(Color::White);
				window->draw(game_over_sprite);
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
					window->clear(Color::White);
					
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
					window->clear(Color::White);

					if (playerPos.y < 133.0f)
					{
						isInside = true;
						//is_playing = false;
						//is_game_over = true;
						window->setKeyRepeatEnabled(false);
					}
				}
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
						window->clear(Color::White);
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
					window->clear(Color::White);
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
					window->clear(Color::White);
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

		}
		else
		{
			//multiplayer mode
			//player1 side
			window->setView(LeftViewB);
			window->draw(background_sprite);
			window->setView(leftView);

			//Draw birds
			draw_overWorld(birds);
			//Draw crabs
			draw_overWorld(crabs);
			//Draw clamps
			draw_overWorld(clamps);
			//Draw fish
			draw_overWorld(fish);
			//Draw ice
			draw_overWorld(iceblocks);
			window->draw(bear->getSprite());
			window->draw(overworld.getTemperature());
			window->draw(overworld.getTemperatureSymbol());
			window->draw(player1.getSprite());

			auto inSafeZone = player1.isPlayerInSafeZone();
			auto isJumping = player1.isPlayerJumping();
			auto isKilledByAnimal = player1.isPlayerKilledByAnimal();
			if (!inSafeZone && !isJumping)
			{
				auto isDrowning = player1.isPlayerDrowning();
				if (isDrowning)
				{
					auto isAnimating = true;
					Stopwatch s_watch;
					
					while (isAnimating)
					{
						auto TimeElapsed = s_watch.elapsed_time();
						animate.drowning_player(TimeElapsed, player1);
						window->draw(background_sprite);
						//Draw birds
						draw_overWorld(birds);
						//Draw crabs
						draw_overWorld(crabs);
						//Draw clamps
						draw_overWorld(clamps);
						//Draw fish
						draw_overWorld(fish);
						//Draw ice
						draw_overWorld(iceblocks);
						window->draw(player1.getSprite());
						window->display();
						window->clear(Color::White);
						if (TimeElapsed >= 1.03f)
						{
							isAnimating = false;
						}
					}
				}
			}

			if (isKilledByAnimal)
			{
				auto isAnimating = true;
				Stopwatch s_watch;
				
				while (isAnimating)
				{
					auto TimeElapsed = s_watch.elapsed_time();
					animate.collision_with_sea_animal(TimeElapsed, player1);
					window->draw(background_sprite);
					//Draw birds
					draw_overWorld(birds);
					//Draw crabs
					draw_overWorld(crabs);
					//Draw clamps
					draw_overWorld(clamps);
					//Draw fish
					draw_overWorld(fish);
					//Draw ice
					draw_overWorld(iceblocks);
					window->draw(player1.getSprite());
					window->display();
					window->clear(Color::White);
					if (TimeElapsed >= 1.03f)
					{
						isAnimating = false;
					}
				}
			}
			//Draw line that separates two screens
			window->draw(line_sprite);
			
			//player2 side
			window->setView(RightViewB);
			window->draw(background_sprite);
			window->setView(rightView);
			draw_overWorld(iceblocks2);
			window->draw(bear2->getSprite());
			draw_overWorld(birds2);
			//Draw crabs
			draw_overWorld(crabs2);
			//Draw clamps
			draw_overWorld(clamps2);
			//Draw fish
			draw_overWorld(fish2);
			window->draw(player2.getSprite());
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
