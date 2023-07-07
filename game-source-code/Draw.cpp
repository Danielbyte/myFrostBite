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
			window.draw(player1.getSprite());
		}
		else
		{
			//multiplayer mode
			//player1 side
			window.setView(LeftViewB);
			window.draw(background_sprite);
			window.setView(leftView);

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
			window.draw(player1.getSprite());

			//Draw line that separates two screens
			window.draw(line_sprite);
			
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
