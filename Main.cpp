#include "Game.h"
#include <MMSystem.h>
#pragma comment(lib, "winmm")
HANDLE handleInput = GetStdHandle(STD_INPUT_HANDLE);
HANDLE handleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
int main() {
	while (true) {
		Game* game = new Game();
		if (game) {
			game->play();
			delete game;
			game = new Game();
		}
	}

}