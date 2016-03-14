#include "MovableObject.h"


MovableObject::MovableObject(std::string location, Coordinate<int> pivotPoint) :
	Object(location, pivotPoint), 
	_moveAccumulation(0)
{
	_currentDirection = Direction::NEITHER;
	_nextDirection = Direction::NEITHER;
	_speed = 0;
}


MovableObject::~MovableObject() {}


MovableObject& MovableObject::setSpeed(float speed) {
	_speed = speed;
	return *this;
}


MovableObject& MovableObject::setNextDirection(Direction direction) {
	_nextDirection = direction;
	return *this;
}


MovableObject& MovableObject::update() {
	if (_speed < 1) {
		_moveAccumulation += _speed;
		if (_moveAccumulation >= 1.0) {
			move(_currentDirection, 1);
			_moveAccumulation = 0;
		}
		(*_currentAnimation)->switchNextModel();
	}
	else {
		move(_currentDirection, 1);
		(*_currentAnimation)->switchNextModel();
	}
	
	_currentDirection = _nextDirection;

	return *this;
}


void MovableObject::move(Direction direction, int step) {
	switch (direction) {
	case Direction::DOWN:
		_pivotPoint.moveDown(step);
		break;
	case Direction::UP:
		_pivotPoint.moveUp(step);
		break;
	case Direction::LEFT:
		_pivotPoint.moveLeft(step);
		break;
	case Direction::RIGHT:
		_pivotPoint.moveRight(step);
		break;
	default:
		break;
	}
}


MovableObject::Direction MovableObject::getOppositeDirection(Direction direction) {
	switch (direction) {
	case MovableObject::Direction::LEFT:
		return MovableObject::Direction::RIGHT;
	case MovableObject::Direction::RIGHT:
		return MovableObject::Direction::LEFT;
	case MovableObject::Direction::UP:
		return MovableObject::Direction::DOWN;
	case MovableObject::Direction::DOWN:
		return MovableObject::Direction::UP;
	default:
		return MovableObject::Direction::NEITHER;
	}
}