#include "ui.h"

Node* make_button(float x, float y, float width, float height, String label) {
	Button* button = malloc(sizeof(*button));
	button->base = (Node){x, y, update_button, draw_button, free_button};
	button->label = NULL;
	append_string(&(button->label), label);
	button->width = width;
	button->height = height;
	button->state = BUTTON_RELEASED;
	return &(button->base);
}

void update_button(Node* node) {
	Button* button = (Button*) node;
	if (button->state == BUTTON_RELEASED) {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mouse_pos = GetMousePosition();
			Vector2 pos = to_screen_coordinates(node->pos);
			if (fabs(mouse_pos.x - pos.x) <= button->width / 2.0f && fabs(mouse_pos.y - pos.y) <= button->height / 2.0f) {
				button->state = BUTTON_PRESSED;
				PlaySound(*get_item(game.sound_effects, "button_click"));
			}
		}
	}
	else if (button->state == BUTTON_PRESSED) {
		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			button->state = BUTTON_RELEASED;

			Vector2 mouse_pos = GetMousePosition();
			Vector2 pos = to_screen_coordinates(node->pos);
			if (fabs(mouse_pos.x - pos.x) <= button->width / 2.0f && fabs(mouse_pos.y - pos.y) <= button->height / 2.0f) {
				//this->on_click();
			}
		}
	}
}

void draw_button(Node* node) {
	Button* button = (Button*) node;
	if (button->state == BUTTON_RELEASED) {
		draw_rectangle(node->pos.x, node->pos.y, button->width, button->height, BLACK);
		draw_rectangle(node->pos.x, node->pos.y + button->height / 2.0f, button->width, 8, GRAY);
		draw_text(*get_item(game.fonts, "romulus"), button->label, node->pos.x, node->pos.y, 48, 8.0f, WHITE);
	}
	else if (button->state == BUTTON_PRESSED) {
		draw_rectangle(node->pos.x, node->pos.y + 6, button->width, button->height, BLACK);
		draw_text(*get_item(game.fonts, "romulus"), button->label, node->pos.x, node->pos.y + 6, 48, 8.0f, WHITE);
	}
	else {
		assert(false);
	}
}

void free_button(Node* node) {
	Button* button = (Button*) node;
	delete_string(&(button->label));
	free(button);
}
