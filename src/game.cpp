#include "game.hpp"
#include "screens/title_screen.hpp"
#include "screens/army_building_screen.hpp"

Game::Game() {
	this->running = true;

	this->fonts["romulus"] = LoadFont("assets/fonts/romulus.png");

	this->sound_effects["button_click"] = LoadSound("assets/sound_effects/button_click.wav");
	this->sound_effects["button_click2"] = LoadSound("assets/sound_effects/button_click2.wav");

	this->textures["atlas"] = LoadTexture("assets/textures/atlas.png");
	this->sprites["tank"] = std::make_pair("atlas", 0);
	this->sprites["city"] = std::make_pair("atlas", 1);
	this->sprites["mountain"] = std::make_pair("atlas", 2);
	this->sprites["water"] = std::make_pair("atlas", 3);

	this->screens["title_screen"] = std::make_shared<TitleScreen>();
	this->screens["army_building_screen"] = std::make_shared<ArmyBuildingScreen>();
	this->current_screen = "title_screen";
}

void Game::update() {
	this->screens[current_screen]->update();
}

void Game::draw() {
	BeginDrawing();
		ClearBackground(RAYWHITE);
		this->screens[current_screen]->draw();
	EndDrawing();
}

Game::~Game() {

}

game::Position Game::from_ui_coordinates_to_screen(game::Position position) {
	float center_x = GetScreenWidth() / 2.0f;
	float center_y = GetScreenHeight() / 2.0f;
	return game::Position(center_x + position.x, center_y - position.y);
}

void Game::draw_sprite(std::string id, game::Position position, float scale) {
	auto sprite = this->sprites[id];
	Texture2D texture = this->textures[sprite.first];
	int index = sprite.second;

	int sprite_size = 32;
	int cols = texture.width / sprite_size;
	int rows = texture.height / sprite_size;
	int clip_x = (index % cols) * sprite_size;
	int clip_y = (index % rows) * sprite_size;
	Rectangle src = {(float)clip_x, (float)clip_y, (float)sprite_size, (float)sprite_size};

	auto pos = this->from_ui_coordinates_to_screen(position);
	pos.x = pos.x - (sprite_size * scale) / 2.0f;
	pos.y = pos.y - (sprite_size * scale) / 2.0f;
	Rectangle dst = {pos.x, pos.y, (sprite_size * scale) , (sprite_size * scale)};

	float rotation = 0;
	Vector2 origin = {(float)sprite_size / 2, (float)sprite_size / 2};
	DrawTexturePro(texture, src, dst, origin, rotation, WHITE);
}
