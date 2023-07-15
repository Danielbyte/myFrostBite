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
			auto isWin = player1.getIfWon();

			if (isWin)
			{
				window->draw(victory_sprite);
				window->display();
				return;
			}

			if (player_state == PlayerState::Dead)
			{
				window->draw(game_over_sprite);
				window->display();
				return;
			}

			auto [playerDistanceToDoor, IglooDoorPos] = player1.distanceToDoor(igloo_house);
			auto inSafeZone = player1.isPlayerInSafeZone();
			auto iglooComplete = igloo_house->isComplete();

			if (inSafeZone && iglooComplete && playerDistanceToDoor.x <= 35.0f && 
				player_state == PlayerState::Alive)
			{
				player1.setState(PlayerState::Winning);
				player1.restartWatch();
			}

			draw(crabs, clamps, birds, fish, igloo_house, bear, iceblocks, player1, overworld);
		}

		else
		{
			//multiplayer mode
			//player1 side
			window->setView(leftView);
			window->draw(background_sprite);
			auto player_stateP1 = player1.getState();
			auto isWinP1 = player1.getIfWon();

			if (isWinP1 || player_stateP1 == PlayerState::Dead)
			{
				if (isWinP1) { window->draw(victory_sprite); }
				if (player_stateP1 == PlayerState::Dead) { window->draw(game_over_sprite); }
				window->draw(line_sprite);
			}

			else
			{
				auto [playerDistanceToDoor, IglooDoorPos] = player1.distanceToDoor(igloo_house);
				auto inSafeZone = player1.isPlayerInSafeZone();
				auto iglooComplete = igloo_house->isComplete();

				if (inSafeZone && iglooComplete && playerDistanceToDoor.x <= 35.0f &&
					player_stateP1 == PlayerState::Alive)
				{
					player1.setState(PlayerState::Winning);
					player1.restartWatch();
				}

				draw(crabs, clamps, birds, fish, igloo_house, bear, iceblocks, player1, overworld);
				window->draw(line_sprite);
			}

			//player2 side
			window->setView(rightView);
			window->draw(background_sprite);
			auto player_stateP2 = player2.getState();
			auto isWinP2 = player2.getIfWon();

			if (isWinP2 || player_stateP2 == PlayerState::Dead)
			{
				if (isWinP2) { window->draw(victory_sprite); }
				if (player_stateP2 == PlayerState::Dead) { window->draw(game_over_sprite); }
			}

			else
			{
				auto [playerDistanceToDoor, IglooDoorPos] = player2.distanceToDoor(igloo_house2);
				auto inSafeZone = player2.isPlayerInSafeZone();
				auto iglooComplete = igloo_house2->isComplete();

				if (inSafeZone && iglooComplete && playerDistanceToDoor.x <= 35.0f &&
					player_stateP2 == PlayerState::Alive)
				{
					player2.setState(PlayerState::Winning);
					player2.restartWatch();
				}

				draw(crabs2, clamps2, birds2, fish2, igloo_house2, bear2, iceblocks2, player2, overworld2);
			}
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
