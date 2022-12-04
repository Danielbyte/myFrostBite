#include "game.h"

void Game::run_game() {
auto game_ptr = std::make_unique<Screen>();

game_ptr -> run();
}
