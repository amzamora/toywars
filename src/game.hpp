#ifndef GAME_H
#define GAME_H

#include <string>
#include <memory>
#include <unordered_map>
#include "raylib.h"

namespace game {
	struct Node {
		virtual void handle_input() {}
		virtual void update() {}
		virtual void draw() {}
		virtual ~Node() {}
	};

	struct Position {
		float x;
		float y;

		Position(float x, float y) : x(x), y(y) {}
		~Position() {}
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

	void update();
	void draw();

	game::Position from_ui_coordinates_to_screen(game::Position position);

private:
	Game();
	~Game();
};

#endif
