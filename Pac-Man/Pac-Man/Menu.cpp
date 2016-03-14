#include "Menu.h"


Menu::Menu() :
	_renderer(new GlRenderer)
{}


Menu::~Menu() {
	delete _state;
	delete _renderer;
}


Menu& Menu::changeGameState(MenuState* state) {
	delete _state;
	_state = state;
	return *this;
}


void Menu::handleRender() {
	_state->renderScreen(*this);
	_state->updateScreen(*this);
}