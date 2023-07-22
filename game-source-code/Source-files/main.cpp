#include "../Header-files/game.h"
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main() {
auto game = Game{};
game.run_game();
return 0;
}
