#include "title_screen.hpp"
#include "../ui/ui.hpp"

TitleScreen::TitleScreen() {
	this->nodes.push_back(std::make_shared<Button>("PLAY", 0, 0, 180, 80, []() {
		Game::instance().current_screen = "army_building_screen";
	}));
	this->nodes.push_back(std::make_shared<Button>("QUIT", 0, - 80 - 20, 180, 80, []() {
		Game::instance().running = false;
	}));
}

void TitleScreen::update() {
	for (size_t i = 0; i < this->nodes.size(); i++) {
		this->nodes[i]->update();
	}
}

void TitleScreen::draw() {
	for (size_t i = 0; i < this->nodes.size(); i++) {
		this->nodes[i]->draw();
	}
}
