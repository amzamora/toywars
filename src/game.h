#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "raylib.h"
#include "dynamic_string.h"
#include "hashmap.h"
#include "list.h"

typedef struct {

} Node;

typedef struct {
	String current_screen;
	HashMap(Node) screens;
	HashMap(Font) fonts;
	HashMap(Sound) sound_effects;
	HashMap(Texture2D) textures;
} Game;
void update_game(Game* game);
void draw_game(Game game);

extern Game game;

#endif
