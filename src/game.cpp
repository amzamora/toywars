#include "game.hpp"
#include "screens/title_screen.hpp"

Game::Game() {
	this->running = true;
	this->fonts[0] = LoadFont("assets/fonts/joystix/joystix monospace.ttf");

	this->screens["title_screen"] = std::make_shared<TitleScreen>();
	this->current_screen = "title_screen";
}

void Game::handle_input() {

}

void Game::update() {

}

void Game::draw() {
	BeginDrawing();
		ClearBackground(RAYWHITE);
	EndDrawing();

	this->screens[current_screen]->draw();
}

Game::~Game() {

}

#include <iostream>
game::Position Game::from_ui_coordinates_to_screen(game::Position position) {
	float center_x = GetScreenWidth() / 2.0f;
	float center_y = GetScreenHeight() / 2.0f;
	return game::Position(center_x + position.x, center_y - position.y);
}
