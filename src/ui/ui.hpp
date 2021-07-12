#ifndef UI_HPP
#define UI_HPP

#include "../game.hpp"

struct Button : game::Node {
	std::string label;
	game::Position position;
	float width;
	float height;

	Button(std::string label, game::Position position, float width, float height) : label(label), position(position), width(width), height(height) {}
	~Button() {}
	virtual void handle_input();
	virtual void update();
	virtual void draw();
};

#endif
