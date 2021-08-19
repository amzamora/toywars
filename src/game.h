#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "raylib.h"
#include "dynamic_string.h"
#include "hashmap.h"
#include "list.h"

struct Node;
typedef struct Node Node;

struct Node {
	Vector2 pos;
	void (*update)(Node*);
	void (*draw)(Node*);
	void (*free)(Node*);
};
void update_node(Node* node);
void draw_node(Node* node);
void free_node(Node* node);

#include "screens/title_screen.h"

typedef struct {
	String current_screen;
	HashMap(Node*) screens;
	HashMap(Font) fonts;
	HashMap(Sound) sound_effects;
	HashMap(Texture2D) textures;
} Game;
void init_game();
void update_game();
void draw_game();
void close_game();

Vector2 to_screen_coordinates(Vector2 pos);
void draw_rectangle(float x, float y, float width, float height, Color color);
void draw_text(Font font, String label, float x, float y, float font_size, float spacing, Color color);

extern Game game;

#endif
