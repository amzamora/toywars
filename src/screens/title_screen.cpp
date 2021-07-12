#include "title_screen.hpp"
#include "../ui/ui.hpp"

TitleScreen::TitleScreen() {
	this->nodes.push_back(std::make_shared<Button>("play", game::Position(0, -50), 180, 80));
}

void TitleScreen::handle_input() {

}

void TitleScreen::update() {

}

void TitleScreen::draw() {
	for (size_t i = 0; i < this->nodes.size(); i++) {
		this->nodes[i]->draw();
	}
}
