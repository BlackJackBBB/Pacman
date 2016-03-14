#include "Pacman.h"
#include "Maze.h"


PacmanLivingMode::PacmanLivingMode(Pacman& pacman)
{
	pacman._nEatenPallets = 0;
	pacman._havePowerPallet = false;
	pacman.setAnimation("pacman_alive");
}


PacmanLivingMode::~PacmanLivingMode() {}


PacmanLivingMode& PacmanLivingMode::planNextMove(GameCharacter& character) {
	Pacman& pacman = dynamic_cast<Pacman&>(character);

	if (pacman._vitalStatus == Pacman::Status::HIT) {
		pacman.changeBehavior(new PacmanDyingMode(pacman));
		return *this;
	}

	Coordinate<int> center = Coordinate<int>(pacman._pivotPoint.getX() + pacman.getWidth() / 2, pacman._pivotPoint.getY() + pacman.getHeight() / 2);

	if (pacman._currentPlace->isPallet(center)) {
		pacman._nEatenPallets++;
		pacman._currentPlace->removePallet(center);
	}

	if (pacman._currentPlace->isPowerPallet(center)) {
		pacman._havePowerPallet = true;
		pacman._currentPlace->removePowerPallet(center);
	}

	for (const auto& character : pacman._currentPlace->getCharacters()) {
		if (character.first != pacman._name &&
			character.second->getPivotPoint().getDistance(pacman._pivotPoint) < pacman.getWidth() / 3 &&
			character.second->getVitalStatus() != GameCharacter::Status::DEAD) {
			character.second->setVitalStatus(Pacman::Status::HIT);
		}
	}

	if (pacman._currentDirection != pacman._nextDirection) {
		if (pacman.probeDirection(pacman._nextDirection)) {
			pacman.move(pacman._nextDirection, 1);
			if (pacman._nextDirection == pacman.getOppositeDirection(pacman._currentDirection)) {
				(*pacman._currentAnimation)->switchModelIterationDirection().switchNextModel();
			}
			else (*pacman._currentAnimation)->switchNextModel();
			pacman._currentDirection = pacman._nextDirection;
			pacman.teleportIfNeeded();
			return *this;
		}
	}
	if (pacman.probeDirection(pacman._currentDirection)) {
		pacman.move(pacman._currentDirection, 1);
		if (pacman._currentDirection != Pacman::Direction::NEITHER) (*pacman._currentAnimation)->switchNextModel();
	}
	pacman.teleportIfNeeded();

	return *this;
}