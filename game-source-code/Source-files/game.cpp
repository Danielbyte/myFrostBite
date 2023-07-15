#include "../Header-files/game.h"

void Game::run_game() 
{
    auto game_ptr = std::make_unique<Engine>();
	game_ptr->run();
}
