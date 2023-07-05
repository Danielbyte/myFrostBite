#include "Engine.h"

void Engine::draw()
{
	window.clear(Color::White);
	//Draw main menu
	if (!inMainMenu)
	{
		//Display other respective views if not in main menu
		if (!splitScreen)
		{
			//single player mode
			window.setView(singlePlayerView);
			window.draw(background_sprite);
			window.draw(player1.getSprite());

			//Draw birds
			if (!birds.empty())
			{
				for (auto& bird : birds)
				{
					window.draw(bird->getSprite());
				}
			}

			//Draw crabs
			if (!crabs.empty())
			{
				for (auto& crab : crabs)
				{
					window.draw(crab->getSprite());
				}
			}
		}
		else
		{
			//multiplayer mode
			//player1 side
			window.setView(LeftViewB);
			window.draw(background_sprite);
			window.draw(line_sprite);
			window.setView(leftView);
			window.draw(player1.getSprite());

			//Draw birds
			if (!birds.empty())
			{
				for (auto& bird : birds)
				{
					window.draw(bird->getSprite());
				}
			}
			
			//player2 side
			window.setView(RightViewB);
			window.draw(background_sprite);
			window.setView(rightView);
			window.draw(player2.getSprite());
		}
	}
	else
	{
		//Draw main menu view
		window.setView(MainmenuView);
		window.draw(menu_sprite);
		window.draw(menu.getCursor());
	}

	window.display();
}