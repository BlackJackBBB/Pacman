#include "Pacman.h"
#include "Maze.h"


Pacman::Pacman(Maze& place, std::string location, Coordinate<int> pivotPoint) :
	GameCharacter(place, location, pivotPoint)
{                          
	if (location != "") {
		changeBehavior(new PacmanLivingMode(*this));
	}
}


Pacman::~Pacman() {
      	delete _behavior;
}


Pacman& Pacman::update() {
	_behavior->planNextMove(*this);
	return *this;
}


Pacman& Pacman::removePowerPallet() {
	_havePowerPallet = false;
	return *this;
}