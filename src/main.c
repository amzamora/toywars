#include "game.h"

int main() {
	// Create window
	InitWindow(800, 450, "Toywars");
	SetTargetFPS(60);

	// Initialize audio
	InitAudioDevice();
	SetConfigFlags(FLAG_MSAA_4X_HINT);

	// Initilize game
	init_game();

	// Main game loop
	while (!WindowShouldClose()) {
		update_game();
		draw_game();
	}

	close_game();

	// Close window
	CloseWindow();

	return 0;
}
