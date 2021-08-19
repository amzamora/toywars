#include "game.h"

Game game;

void update_node(Node* node) {node->update(node);}
void draw_node(Node* node) {node->draw(node);}
void free_node(Node* node) {node->free(node);}

void init_game() {
	game.fonts = NULL;
	game.screens = NULL;
	game.sound_effects = NULL;
	game.textures = NULL;
	game.current_screen = "title_screen";

	// Load fonts
	insert_item(game.fonts, "romulus", LoadFont("assets/fonts/romulus.png"));

	// Load sound effects
	insert_item(game.sound_effects, "button_click", LoadSound("assets/sound_effects/button_click.wav"));
	insert_item(game.sound_effects, "button_click2", LoadSound("assets/sound_effects/button_click2.wav"));

	// Create screens
	insert_item(game.screens, "title_screen", make_title_screen());
}

void update_game() {
	update_node(*get_item(game.screens, game.current_screen));
}

void draw_game() {
	BeginDrawing();
		ClearBackground(RAYWHITE);
		draw_node(*get_item(game.screens, game.current_screen));
	EndDrawing();
}

Vector2 to_screen_coordinates(Vector2 pos) {
	float center_x = GetScreenWidth() / 2.0f;
	float center_y = GetScreenHeight() / 2.0f;
	Vector2 result = {center_x + pos.x, center_y - pos.y};
	return result;
}

void draw_rectangle(float x, float y, float width, float height, Color color) {
	Vector2 pos = {x, y};
	pos = to_screen_coordinates(pos);
	DrawRectangle(pos.x - width / 2.0f, pos.y - height / 2.0f, width, height, color);
}

void draw_text(Font font, String label, float x, float y, float font_size, float spacing, Color color) {
	Vector2 pos = to_screen_coordinates((Vector2){x, y});
	Vector2 text_dimensions = MeasureTextEx(font, label, font_size, spacing);
	float text_width = text_dimensions.x;
	float text_height = text_dimensions.y;
	pos = (Vector2){pos.x - text_width / 2.0f - 6, pos.y - text_height / 2.0f};
	DrawTextEx(font, label, pos, font_size, spacing, color);
}

void close_game() {
	delete_hashmap(game.fonts);
	delete_hashmap(game.sound_effects);
	delete_hashmap(game.textures);
	for (size_t i = 0; i < capacity(game.screens); i++) {
		if (game.screens->buckets[i].state == Filled) {
			printf("HERE\n");
			free_node(game.screens->buckets[i].value);
		}
	}
	delete_hashmap(game.screens);
}
