#include "ui.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

void Button::handle_input() {

}

void Button::update() {
	if (this->state == BUTTON_RELEASED) {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse_pos = GetMousePosition();
			game::Position pos = Game::instance().from_ui_coordinates_to_screen(this->position);
			if (fabs(mouse_pos.x - pos.x) <= this->width / 2.0f && fabs(mouse_pos.y - pos.y) <= this->height / 2.0f) {
				this->state = BUTTON_PRESSED;
				PlaySound(Game::instance().sound_effects["button_click"]);
			}
		}
	}
	else if (this->state == BUTTON_PRESSED) {
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			this->state = BUTTON_RELEASED;
		}
	}
}

void Button::draw() {
	if (this->state == BUTTON_RELEASED) {
		game::Position pos = Game::instance().from_ui_coordinates_to_screen(this->position);
		DrawRectangle(pos.x - this->width / 2.0f, pos.y - this->height / 2.0f, this->width, this->height, BLACK);
		DrawRectangle(pos.x - this->width / 2.0f, pos.y + this->height / 2.0f, this->width, 8, GRAY);

		float font_size = 48;
		Vector2 text_dimensions = MeasureTextEx(Game::instance().fonts["romulus"], this->label.c_str(), font_size, 4.0f);
		float text_width = text_dimensions.x;
		float text_height = text_dimensions.y;
		DrawTextEx(Game::instance().fonts["romulus"], this->label.c_str(), {pos.x - text_width / 2.0f - 6, pos.y - text_height / 2.0f}, font_size, 8.0f, WHITE);
	}
	else if (this->state == BUTTON_PRESSED) {
		game::Position pos = Game::instance().from_ui_coordinates_to_screen(this->position);
		DrawRectangle(pos.x - this->width / 2.0f, pos.y - this->height / 2.0f + 8 - 2, this->width, this->height, BLACK);
		DrawRectangle(pos.x - this->width / 2.0f, pos.y - this->height / 2.0f, this->width, 8 - 2, GRAY);

		float font_size = 48;
		Vector2 text_dimensions = MeasureTextEx(Game::instance().fonts["romulus"], this->label.c_str(), font_size, 4.0f);
		float text_width = text_dimensions.x;
		float text_height = text_dimensions.y;
		DrawTextEx(Game::instance().fonts["romulus"], this->label.c_str(), {pos.x - text_width / 2.0f - 6, pos.y - text_height / 2.0f + 8 - 2}, font_size, 8.0f, WHITE);
	}
	else {
		assert(false);
	}
}
