#include "ui.hpp"

void Button::handle_input() {

}

void Button::update() {

}

#include <iostream>
void Button::draw() {
	auto pos = Game::instance().from_ui_coordinates_to_screen(this->position);
	DrawRectangle(pos.x - this->width / 2.0f, pos.y - this->height / 2.0f, this->width, this->height, BLACK);
	DrawRectangle(pos.x - this->width / 2.0f, pos.y + this->height / 2.0f, this->width, 8, GRAY);

	float font_size = 48;
	Vector2 text_dimensions = MeasureTextEx(Game::instance().fonts[0], this->label.c_str(), font_size, 4.0f);
	float text_width = text_dimensions.x;
	float text_height = text_dimensions.y;
	DrawTextEx(Game::instance().fonts[0], this->label.c_str(), {pos.x - text_width / 2.0f, pos.y - text_height / 2.0f}, font_size, 4.0f, WHITE);
}
