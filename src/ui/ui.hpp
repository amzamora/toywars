#ifndef UI_HPP
#define UI_HPP

#include <vector>
#include <functional>
#include "../game.hpp"

typedef enum {
	BUTTON_RELEASED,
	BUTTON_PRESSED
} ButtonState;

struct Button : game::Node {
	std::string label;
	game::Position position;
	float width;
	float height;
	ButtonState state;
	std::function<void()> on_click;

	Button(std::string label, game::Position position, float width, float height) : label(label), position(position), width(width), height(height), state(BUTTON_RELEASED), on_click([](){}) {}
	Button(std::string label, game::Position position, float width, float height, std::function<void()> on_click) : label(label), position(position), width(width), height(height), state(BUTTON_RELEASED), on_click(on_click) {}
	~Button() {}
	virtual void update();
	virtual void draw();
};

struct Card : game::Node {
	std::string texture;
	game::Position position;
	std::vector<std::shared_ptr<game::Node>> nodes;

	Card(std::string texture, game::Position position) : texture(texture), position(position) {}
	~Card() {}
	virtual void update();
	virtual void draw();
};

#endif
