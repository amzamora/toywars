#ifndef UI_HPP
#define UI_HPP

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

	Button(std::string label, game::Position position, float width, float height) : label(label), position(position), width(width), height(height), state(BUTTON_RELEASED) {}
	~Button() {}
	virtual void handle_input();
	virtual void update();
	virtual void draw();
};

#endif
