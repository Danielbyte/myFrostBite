#include "Engine.h"

void Engine::draw()
{
	window.clear(Color::White);
	//Draw main menu
	if (!inMainMenu)
	{
		//Display other respective views if not in main menu
	}
	else
	{
		//Draw main menu view
		window.setView(MainmenuView);
		window.draw(background_sprite);
		window.draw(menu.getCursor());
	}

	window.display();
}