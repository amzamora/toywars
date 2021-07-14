#include "ui.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

void Button::update() {
	if (this->state == BUTTON_RELEASED) {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse_pos = GetMousePosition();
			Vector2 pos = Game::instance().to_screen_coordinates(this->position);
			if (fabs(mouse_pos.x - pos.x) <= this->width / 2.0f && fabs(mouse_pos.y - pos.y) <= this->height / 2.0f) {
				this->state = BUTTON_PRESSED;
				PlaySound(Game::instance().sound_effects["button_click"]);
			}
		}
	}
	else if (this->state == BUTTON_PRESSED) {
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			this->state = BUTTON_RELEASED;

			Vector2 mouse_pos = GetMousePosition();
			Vector2 pos = Game::instance().to_screen_coordinates(this->position);
			if (fabs(mouse_pos.x - pos.x) <= this->width / 2.0f && fabs(mouse_pos.y - pos.y) <= this->height / 2.0f) {
				this->on_click();
			}
		}
	}
}

void Button::draw() {
	if (this->state == BUTTON_RELEASED) {
		Game::instance().draw_rectangle(this->position.x, this->position.y, this->width, this->height, BLACK);
		Game::instance().draw_rectangle(this->position.x, this->position.y + this->height / 2.0f, this->width, 8, GRAY);
		Game::instance().draw_text(Game::instance().fonts["romulus"], this->label, this->position.x, this->position.y, 48, 8.0f, WHITE);
	}
	else if (this->state == BUTTON_PRESSED) {
		Game::instance().draw_rectangle(this->position.x, this->position.y + 6, this->width, this->height, BLACK);
		Game::instance().draw_text(Game::instance().fonts["romulus"], this->label, this->position.x, this->position.y + 6, 48, 8.0f, WHITE);
	}
	else {
		assert(false);
	}
}

void Card::update() {

}

void Card::draw() {
	Game::instance().draw_sprite("tank", this->position, 3);
}
