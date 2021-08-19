#include "title_screen.h"
#include "../ui/ui.h"

Node* make_title_screen() {
	TitleScreen* ts = malloc(sizeof(*ts));
	ts->base = (Node){(Vector2){0, 0}, update_title_screen, draw_title_screen, free_title_screen};
	ts->nodes = NULL;

	push_back(ts->nodes, make_button(0, 0, 180, 80, "PLAY"));
	push_back(ts->nodes, make_button(0, -100, 180, 80, "QUIT"));

	return &(ts->base);
}

void update_title_screen(Node* node) {
	TitleScreen* ts = (TitleScreen*) node;
	for (size_t i = 0; i < list_size(ts->nodes); i++) {
		update_node(ts->nodes[i]);
	}
}

void draw_title_screen(Node* node) {
	TitleScreen* ts = (TitleScreen*) node;
	for (size_t i = 0; i < list_size(ts->nodes); i++) {
		draw_node(ts->nodes[i]);
	}
}

void free_title_screen(Node* node) {
	TitleScreen* ts = (TitleScreen*) node;
	for (size_t i = 0; i < list_size(ts->nodes); i++) {
		free_node(ts->nodes[i]);
	}
	delete_list(ts->nodes);
	free(ts);
}
