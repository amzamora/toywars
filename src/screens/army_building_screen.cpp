#include "army_building_screen.hpp"
#include "../ui/ui.hpp"

ArmyBuildingScreen::ArmyBuildingScreen() {
	this->nodes.push_back(std::make_shared<Card>("", 0, 0));
}

void ArmyBuildingScreen::update() {
	for (size_t i = 0; i < this->nodes.size(); i++) {
		this->nodes[i]->update();
	}
}

void ArmyBuildingScreen::draw() {
	for (size_t i = 0; i < this->nodes.size(); i++) {
		this->nodes[i]->draw();
	}
}
