#include "game.hpp"

int main() {
	// Create window
	InitWindow(800, 450, "Toywars");
	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose() && Game::instance().running) {
		Game::instance().handle_input();
		Game::instance().update();
		Game::instance().draw();
	}

	// Close window
	CloseWindow();

	return 0;
}
