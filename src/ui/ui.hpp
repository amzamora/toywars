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
	Vector2 position;
	float width;
	float height;
	ButtonState state;
	std::function<void()> on_click;

	Button(std::string label, float x, float y, float width, float height) : label(label), position({x, y}), width(width), height(height), state(BUTTON_RELEASED), on_click([](){}) {}
	Button(std::string label, float x, float y, float width, float height, std::function<void()> on_click) : label(label), position({x, y}), width(width), height(height), state(BUTTON_RELEASED), on_click(on_click) {}
	~Button() {}
	virtual void update();
	virtual void draw();
};

struct Card : game::Node {
	std::string texture;
	Vector2 position;
	std::vector<std::shared_ptr<game::Node>> nodes;

	Card(std::string texture, float x, float y) : texture(texture), position({x, y}) {}
	~Card() {}
	virtual void update();
	virtual void draw();
};

#endif
