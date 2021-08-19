#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "../game.h"

typedef struct {
	Node base;
	List(Node*) nodes;
} TitleScreen;
Node* make_title_screen();
void update_title_screen(Node* node);
void draw_title_screen(Node* node);
void free_title_screen(Node* node);

#endif
