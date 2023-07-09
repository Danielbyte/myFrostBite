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
