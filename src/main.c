#include "raylib.h"

int main() {
	// Create window
	InitWindow(800, 450, "Hello raylib!");
	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(RAYWHITE);
		EndDrawing();
	}

	// Close window
	CloseWindow();

	return 0;
}
