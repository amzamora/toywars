#include "game.hpp"

int main() {
	// Create window
	InitWindow(800, 450, "Toywars");
	SetTargetFPS(60);

	// Initialize audio
	InitAudioDevice();
	SetConfigFlags(FLAG_MSAA_4X_HINT);

	// Main game loop
	while (!WindowShouldClose() && Game::instance().running) {
		Game::instance().update();
		Game::instance().draw();
	}

	// Close window
	CloseWindow();

	return 0;
}
