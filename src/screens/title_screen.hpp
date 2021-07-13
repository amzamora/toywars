#ifndef TITLE_SCREEN_HPP
#define TITLE_SCREEN_HPP

#include <vector>
#include "../game.hpp"

struct TitleScreen : game::Node {
	std::vector<std::shared_ptr<game::Node>> nodes;

	TitleScreen();
	~TitleScreen() {}
	virtual void update();
	virtual void draw();
};

#endif
