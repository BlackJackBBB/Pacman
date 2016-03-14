#include "Ghost.h"
#include "Maze.h"


GhostHomeReturnMode::GhostHomeReturnMode(Ghost& ghost) :
	_pathToHome(ghost.findPath(ghost._currentPlace->getGhostsHome().getEntrancePoint())),
	_enteringHome(false) 
{
	ghost._speed = 2.0;
	ghost.setAnimation(convertToGhostsAnimationName(_pathToHome.front()));
	planNextMove(ghost);
}


GhostHomeReturnMode::~GhostHomeReturnMode() {}


GhostHomeReturnMode& GhostHomeReturnMode::planNextMove(GameCharacter& character) {
	Ghost& ghost = dynamic_cast<Ghost&>(character);

	if (_enteringHome) {
		if (ghost._pivotPoint.getY() == ghost._currentPlace->getObjectPivotPoint("ghosts_home_position_2").getY()) ghost.changeBehavior(new GhostHomeExitMode(ghost));
		return *this;
	}

	if (ghost._pivotPoint == ghost._currentPlace->getGhostsHome().getEntrancePoint()) {
		_enteringHome = true;
		if (ghost._pivotPoint.getY() > ghost._currentPlace->getObjectPivotPoint("ghosts_home_position_2").getY()) ghost._nextDirection = Ghost::Direction::DOWN;
		else if (ghost._pivotPoint.getY() < ghost._currentPlace->getObjectPivotPoint("ghosts_home_position_2").getY()) ghost._nextDirection = Ghost::Direction::UP;
		else if (ghost._pivotPoint.getX() > ghost._currentPlace->getObjectPivotPoint("ghosts_home_position_2").getX()) ghost._nextDirection = Ghost::Direction::LEFT;
		else if (ghost._pivotPoint.getX() < ghost._currentPlace->getObjectPivotPoint("ghosts_home_position_2").getX()) ghost._nextDirection = Ghost::Direction::RIGHT;
		if (ghost._nextDirection != ghost._currentDirection) {
			ghost._currentDirection = ghost._nextDirection;
			ghost.setAnimation(convertToGhostsAnimationName(ghost._currentDirection));
		}
	}
	else {
		ghost._nextDirection = _pathToHome.front();
		if (ghost._currentDirection != ghost._nextDirection) {
			ghost._currentDirection = ghost._nextDirection;
			ghost.setAnimation(convertToGhostsAnimationName(ghost._currentDirection));
		}
		_pathToHome.pop_front();
	}
	return *this;
}


std::string GhostHomeReturnMode::convertToGhostsAnimationName(Ghost::Direction direction) {
	switch (direction) {
	case Ghost::Direction::LEFT:
		return "eye_left";
	case Ghost::Direction::RIGHT:
		return "eye_right";
	case Ghost::Direction::DOWN:
		return "eye_down";
	case Ghost::Direction::UP:
		return "eye_up";
	default:
		return "";
	}
}