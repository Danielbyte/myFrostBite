#include "Engine.h"

//This file handles the input from the main menu and gameplay
void Engine::MenuInput()
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			//handle player quiting game play screen
			if (sf::Keyboard::isKeyPressed(Keyboard::Escape))
			{
				inMainMenu = true;
				isPlaying = false;
				splitScreen = false;
			}

			if (sf::Keyboard::isKeyPressed(Keyboard::Down) && inMainMenu)
			{
				if (menu.getCursorLevel() == 4)
				{ 
					menu.setCursorLevel(1);
				}
				else
				{
					menu.setCursorLevel(menu.getCursorLevel() + 1);
				}
			}

			if (sf::Keyboard::isKeyPressed(Keyboard::Up) && inMainMenu)
			{
				if (menu.getCursorLevel() == 1)
				{
					menu.setCursorLevel(4);
				}
				else
				{
					menu.setCursorLevel(menu.getCursorLevel() - 1);
				}
			}
		}
	}

	//Butto handling
	if (inMainMenu)
	{
		if (sf::Keyboard::isKeyPressed(Keyboard::Enter))
		{
			if (menu.getCursorLevel() == 1)
			{
				inMainMenu = false;
				splitScreen = false;
				isPlaying = true;
			}

			if (menu.getCursorLevel() == 2)
			{
				inMainMenu = false;
				splitScreen = true;
			}

			if (menu.getCursorLevel() == 3)
			{
				//should display a window of instructions
			}

			if (menu.getCursorLevel() == 4)
			{
				//close game if player clicks on quit game
				window.close();
			}
		}

		menu.update();
	}

	player1.handleInput();
}