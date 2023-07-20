#include "../Header-files/Engine.h"

//This file handles the input from the main menu and gameplay
void Engine::handleInput()
{
	Event event;
	auto keyPressed = false;
	while (window->pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			keyPressed = true;
			//handle player quiting game play screen
			if (sf::Keyboard::isKeyPressed(Keyboard::Escape))
			{
				inMainMenu = true;
				isPlaying = false;
				splitScreen = false;
				needToSpawn = true;
				reInitialise = true;
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

			if (sf::Keyboard::isKeyPressed(Keyboard::Enter) && inInstructionsMenu)
			{
				inInstructionsMenu = false;
				menu.setCursorLevel(1);
				inMainMenu = true;
				keyPressed = false;
			}
		}

		if (event.type == Event::Closed)
		{
			quit = true;
			window->close();
		}

	}

	//Button handling
	if (inMainMenu)
	{
		if (sf::Keyboard::isKeyPressed(Keyboard::Enter) && keyPressed)
		{
			if (menu.getCursorLevel() == 1)
			{
				inMainMenu = false;
				splitScreen = false;
				isPlaying = true;
				canCreateIce = true;
				overworld_watch.restart_timer();
				overworld_watch2.restart_timer();
				overworld.initialize_temperature();
			}

			if (menu.getCursorLevel() == 2)
			{
				InitialiseStatesForMultiPlayer();
			}

			if (menu.getCursorLevel() == 3)
			{
				//should display a window of instructions
				inInstructionsMenu = true;
				//inMainMenu = false;
			}

			if (menu.getCursorLevel() == 4)
			{
				//close game if player clicks on quit game
				quit = true;
				window->close();
			}
		}

		menu.update();
	}

	if (isPlaying)
	{
		player1->handleInput(keyPressed);
		player2->handleInput(keyPressed);
	}

}

void Engine::InitialiseStatesForMultiPlayer()
{
	inMainMenu = false;
	splitScreen = true;
	isPlaying = true;
	canCreateIce = true;
	canCreateIce2 = true;
	overworld_watch.restart_timer();
	overworld_watch2.restart_timer();
	overworld.initialize_temperature();
	overworld2.initialize_temperature();
	overworld.mSetTemperatureHUD();
	overworld2.mSetTemperatureHUD();
	overworld.setMultiPlayerMode();
	overworld2.setMultiPlayerMode();
	control_fish->setMultiplayerBounds();
	control_birds->setMultiPlayerBounds();
	control_crabs->setMultiPlayerBounds();
	control_clamps->setMultiPlayerBounds();

	//player1
	player1->setBoundaries(mLeftBoundary, mRightBoundary);
	player1->msetHUDPosition(mLivesHUDPos);
	control_ice->setNewBoundaries();
	control_ice->mSetIceOffset();
	bear->mSetSpawnPosition();
	bear->mSetBorders();
	igloo_house->mSetPosition();
	//player2
	player2->setBoundaries(mLeftBoundary, mRightBoundary);
	player2->msetHUDPosition(mLivesHUDPos);
	bear2->mSetSpawnPosition();
	bear2->mSetBorders();
	igloo_house2->mSetPosition();
}