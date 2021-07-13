#ifndef ARMY_BUILDING_SCREEN_HPP
#define ARMY_BUILDING_SCREEN_HPP

#include <vector>
#include "../game.hpp"

struct ArmyBuildingScreen : game::Node {
	std::vector<std::shared_ptr<game::Node>> nodes;

	ArmyBuildingScreen();
	~ArmyBuildingScreen() {}
	virtual void update();
	virtual void draw();
};

#endif
