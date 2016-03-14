#include "Ghost.h"
#include "Maze.h"


Ghost::Ghost(Maze& place, std::string location, Coordinate<int> pivotPoint) :
	GameCharacter(place, location, pivotPoint)
{
	if (location != "") {
		_behavior = new GhostHomeMode(*this);
	}
}


Ghost::~Ghost() {
	delete _behavior;
}


Ghost& Ghost::update() {
	if (_speed < 1) {
		_moveAccumulation += _speed;
		if (_moveAccumulation >= 1.0) {
			move(_currentDirection, 1);
			_moveAccumulation = 0;
			if (teleportIfNeeded()) _behavior->findOppositeWallPosition(*this);
			_behavior->planNextMove(*this);
		}
		(*_currentAnimation)->switchNextModel();
	}
	else if (_speed > 1) {
		_moveAccumulation = _speed;
		while (_moveAccumulation >= 1) {
			move(_currentDirection, 1);
			_moveAccumulation -= 1;
			if (teleportIfNeeded()) _behavior->findOppositeWallPosition(*this);
			_behavior->planNextMove(*this);
		}
		(*_currentAnimation)->switchNextModel();
	}
	else {
		move(_currentDirection, 1);
		(*_currentAnimation)->switchNextModel();
		if (teleportIfNeeded()) _behavior->findOppositeWallPosition(*this);
		_behavior->planNextMove(*this);
	}
	
	return *this;
}