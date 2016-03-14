#include "Pacman.h"
#include "Maze.h"


PacmanDyingMode::PacmanDyingMode(Pacman& pacman) :
	_modelCounter(1)
{
	pacman.setAnimation("pacman_dead");
}


PacmanDyingMode::~PacmanDyingMode() {}


PacmanDyingMode& PacmanDyingMode::planNextMove(GameCharacter& character) {
	Pacman& pacman = dynamic_cast<Pacman&>(character);

	if (_modelCounter < pacman.getCurrentAnimation().getNumberOfModels()) {
		_modelCounter++;
		(*pacman._currentAnimation)->switchNextModel();
	}
	else {
		pacman._vitalStatus = Pacman::Status::DEAD;
	}

	return *this;
}
