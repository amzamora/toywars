#ifndef UI_H
#define UI_H

#include "../game.h"

typedef enum {
	BUTTON_RELEASED,
	BUTTON_PRESSED
} ButtonState;


typedef struct {
	Node base;
	String label;
	float width;
	float height;
	ButtonState state;
	void (*on_click)(Node*);
} Button;
Node* make_button(float x, float y, float width, float height, String label);
void update_button(Node* node);
void draw_button(Node* node);
void free_button(Node* node);

#endif
