#include "Engine.h"

void Engine::draw()
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
			window->draw(igloo_house->getSprite());
			window->draw(bear->getSprite());
			window->draw(player1.getSprite());

			auto inSafeZone = player1.isPlayerInSafeZone();
			auto isJumping = player1.isPlayerJumping();
			auto isKilledByAnimal = player1.isPlayerKilledByAnimal();
			auto isKilledByBear = player1.isKilledByBear();
			auto iglooComplete = igloo_house->isComplete();
			auto [playerDistanceToDoor, IglooDoorPos] = player1.distanceToDoor(igloo_house);

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
					window->draw(igloo_house->getSprite());
					window->draw(bear->getSprite());
					window->draw(player1.getSprite());
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
					player1.set_to_dead();
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
						window->draw(igloo_house->getSprite());
						window->draw(bear->getSprite());
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
				player1.set_to_dead();
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
					window->draw(igloo_house->getSprite());
					window->draw(bear->getSprite());
					window->draw(player1.getSprite());
					window->display();
					window->clear(Color::White);
					if (TimeElapsed >= 1.03f)
					{
						isAnimating = false;
					}
				}
			}

			if (isKilledByBear)
			{
				auto isAnimating = true;
				Stopwatch s_watch;
				player1.set_to_dead();
				while (isAnimating)
				{
					auto TimeElapsed = s_watch.elapsed_time();
					animate.killed_by_bear(TimeElapsed, player1);
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
					window->draw(igloo_house->getSprite());
					window->draw(bear->getSprite());
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
					player1.set_to_dead();
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
				player1.set_to_dead();
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
