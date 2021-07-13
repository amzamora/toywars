#include "title_screen.hpp"
#include "../ui/ui.hpp"

TitleScreen::TitleScreen() {
	this->nodes.push_back(std::make_shared<Button>("PLAY", game::Position(0, -50), 180, 80));
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
