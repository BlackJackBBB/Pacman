#include "Ghost.h"
#include "Maze.h"


GhostHuntingMode::GhostHuntingMode(Ghost& ghost) :
	_chasingPacman(false),
	_lastSeenPacmanPosition(-1, -1),
	_seeingNextDirection(false) 
{
	planNextMove(ghost);
	ghost.setAnimation(convertToGhostsAnimationName(ghost._currentDirection));
	ghost._speed = 1;
}


GhostHuntingMode::~GhostHuntingMode() {}


GhostHuntingMode& GhostHuntingMode::planNextMove(GameCharacter& character) {
	Ghost& ghost = dynamic_cast<Ghost&>(character);

	if (ghost._pivotPoint.getDistance(ghost._currentPlace->getCharacter("pacman").getPivotPoint()) <= ghost.getWidth() / 4 &&
		ghost._currentPlace->getCharacter("pacman").getVitalStatus() != GameCharacter::Status::DEAD) {
		ghost._currentPlace->getCharacter("pacman").setVitalStatus(GameCharacter::Status::HIT);
		return *this;
	}

	if (_chasingPacman) {
		if (_lastSeenPacmanPosition == ghost._pivotPoint) {
			ghost._currentDirection = ghost._nextDirection;
			ghost.setAnimation(convertToGhostsAnimationName(ghost._currentDirection));
			findOppositeWallPosition(ghost);
			_chasingPacman = false;
			_lastSeenPacmanPosition = Coordinate<int>(-1, -1);
		}
	}
	else {
		ghost._nextDirection = chooseDirection(ghost);
		if (ghost._currentDirection != ghost._nextDirection) {
			ghost._currentDirection = ghost._nextDirection;
			ghost.setAnimation(convertToGhostsAnimationName(ghost._currentDirection));
			findOppositeWallPosition(ghost);
		}
	}
	lookForPacman(ghost);

	return *this;
}


void GhostHuntingMode::lookForPacman(Ghost& ghost) {
	if (ghost._currentPlace->getCharacter("pacman").getPivotPoint().isBetween(ghost._pivotPoint, _oppositeWallPosition)) {
		_lastSeenPacmanPosition = ghost._currentPlace->getCharacter("pacman").getPivotPoint();
		_seeingNextDirection = true;
		_chasingPacman = true;
	}
	else if (_seeingNextDirection) {
		ghost._nextDirection = ghost._currentPlace->getCharacter("pacman").getCurrentDirection();
		_seeingNextDirection = false;
	}
}