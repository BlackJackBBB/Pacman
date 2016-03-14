#include "Ghost.h"
#include "Maze.h"


GhostScatterMode::GhostScatterMode(Ghost& ghost, unsigned modeLenght) :
	_escapingPacman(false),
	_modeLenght(modeLenght)
{
	ghost._speed = 0.5;
	_animationLenght = modeLenght - _timeBeforeEnd;
	ghost.setAnimation("ghost_scared");
	planNextMove(ghost);
	findOppositeWallPosition(ghost);
}


GhostScatterMode::~GhostScatterMode() {}


GhostScatterMode& GhostScatterMode::planNextMove(GameCharacter& character) {
	Ghost& ghost = dynamic_cast<Ghost&>(character);

	_modeLenght--;
	_animationLenght--;

	if (_modeLenght <= _timeBeforeEnd && _animationLenght == 0) {
		if (ghost.getCurrentAnimation().getName() == "ghost_scared") ghost.setAnimation("ghost_special");
		else ghost.setAnimation("ghost_scared");
		_animationLenght = _timeBetweenAnimations;
	}

	if (ghost._vitalStatus == Ghost::Status::HIT) {
		ghost._vitalStatus = Ghost::Status::DEAD;
		ghost.changeBehavior(new GhostHomeReturnMode(ghost));
		return *this;
	}
	else {
		if (_escapingPacman) {
			ghost._currentDirection = ghost._nextDirection;
			findOppositeWallPosition(ghost);
			_escapingPacman = false;
		}
		else {
			ghost._nextDirection = chooseDirection(ghost);
			if (ghost._nextDirection != ghost._currentDirection) {
				ghost._currentDirection = ghost._nextDirection;
				findOppositeWallPosition(ghost);
			}
		}
		lookForPacman(ghost);
	}

	if (_modeLenght == 0) ghost.changeBehavior(new GhostHuntingMode(ghost));
	return *this;
}


void GhostScatterMode::lookForPacman(Ghost& ghost) {
	if (ghost._currentPlace->getCharacter("pacman").getPivotPoint().isBetween(ghost._pivotPoint, _oppositeWallPosition)) {
		ghost._nextDirection = ghost.getOppositeDirection(ghost._currentDirection);
		_escapingPacman = true;
	}
}