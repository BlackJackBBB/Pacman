#include "Ghost.h"
#include "Maze.h"


GhostHomeExitMode::GhostHomeExitMode(Ghost& ghost) {
	ghost._vitalStatus = Ghost::Status::ALIVE;
	ghost._currentDirection = chooseDirection(ghost);
	ghost._nextDirection = Ghost::Direction::NEITHER;
	ghost.setAnimation(convertToGhostsAnimationName(ghost._currentDirection));
	ghost._currentPlace->getGhostsHome().open();
	ghost._speed = 0.5;
}


GhostHomeExitMode::~GhostHomeExitMode() {}


GhostHomeExitMode& GhostHomeExitMode::planNextMove(GameCharacter& character) {
	Ghost& ghost = dynamic_cast<Ghost&>(character);

	if (ghost._pivotPoint == ghost._currentPlace->getGhostsHome().getEntrancePoint()) {
		ghost._currentDirection = Ghost::Direction::NEITHER;
		ghost._nextDirection = Ghost::Direction::NEITHER;
		ghost._currentPlace->getGhostsHome().close();
		ghost.changeBehavior(new GhostHuntingMode(ghost));
	}
	else {
		ghost._currentPlace->getGhostsHome().open();
		ghost._nextDirection = chooseDirection(ghost);
		if (ghost._nextDirection != ghost._currentDirection) {
			ghost._currentDirection = ghost._nextDirection;
			ghost.setAnimation(convertToGhostsAnimationName(ghost._currentDirection));
		}
	}

	return *this;
}


Ghost::Direction GhostHomeExitMode::chooseDirection(Ghost& ghost) {
	if (ghost._pivotPoint.getX() < ghost._currentPlace->getGhostsHome().getEntrancePoint().getX()) return Ghost::Direction::RIGHT;
	if (ghost._pivotPoint.getX() > ghost._currentPlace->getGhostsHome().getEntrancePoint().getX()) return Ghost::Direction::LEFT;
	if (ghost._pivotPoint.getX() == ghost._currentPlace->getGhostsHome().getEntrancePoint().getX()) return Ghost::Direction::UP;
}