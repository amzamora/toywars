#include "game.h"

int main() {
	// Create window
	InitWindow(800, 450, "Toywars");
	SetTargetFPS(60);

	// Initialize audio
	InitAudioDevice();
	SetConfigFlags(FLAG_MSAA_4X_HINT);

	// Initilize game


	// Main game loop
	while (!WindowShouldClose()) {
		draw_game(game);
	}

	// Close window
	CloseWindow();

	return 0;
}
