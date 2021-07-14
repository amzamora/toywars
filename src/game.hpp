#ifndef GAME_H
#define GAME_H

#include <string>
#include <memory>
#include <unordered_map>
#include <utility>
#include "raylib.h"

namespace game {
	struct Node {
		virtual void handle_input() {}
		virtual void update() {}
		virtual void draw() {}
		virtual ~Node() {}
	};
}

class Game {
public:
	static Game& instance() {
		static Game instance;
		return instance;
	}

	float fps;
	bool running;
	std::string current_screen;
	std::unordered_map<std::string, std::shared_ptr<game::Node>> screens;
	std::unordered_map<std::string, Font> fonts;
	std::unordered_map<std::string, Sound> sound_effects;
	std::unordered_map<std::string, Texture2D> textures;
	std::unordered_map<std::string, std::pair<std::string, int>> sprites;

	void update();
	void draw();

	Vector2 to_screen_coordinates(Vector2 position);
	void draw_rectangle(float x, float y, float width, float height, Color color);
	void draw_text(Font font, std::string label, float x, float y, float font_size, float spacing, Color color);
	void draw_sprite(std::string id, Vector2 position, float scale = 1.0f);

private:
	Game();
	~Game();
};

#endif
