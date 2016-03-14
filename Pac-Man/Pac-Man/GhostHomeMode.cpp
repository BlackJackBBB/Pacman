#include "Ghost.h"
#include "Maze.h"


GhostHomeMode::GhostHomeMode(Ghost& ghost) {
	ghost.setAnimation("ghost_up");
	ghost._currentDirection = Ghost::Direction::UP;
	ghost._nextDirection = Ghost::Direction::NEITHER;
	ghost._speed = 0.5;
}


GhostHomeMode::~GhostHomeMode() {}


GhostHomeMode& GhostHomeMode::planNextMove(GameCharacter& character) {
	Ghost& ghost = dynamic_cast<Ghost&>(character);

	ghost._nextDirection = chooseDirection(ghost);
	if (ghost._nextDirection != ghost._currentDirection) {
		ghost._currentDirection = ghost._nextDirection;
		ghost.setAnimation(convertToGhostsAnimationName(ghost._currentDirection));
	}

	return *this;
}


Ghost::Direction GhostHomeMode::chooseDirection(Ghost& ghost) {
	if (ghost.probeDirection(ghost._currentDirection)) return ghost._currentDirection;
	else return ghost.getOppositeDirection(ghost._currentDirection);
}