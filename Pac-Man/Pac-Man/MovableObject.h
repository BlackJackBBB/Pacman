#pragma once
#include "Object.h"

class MovableObject : public Object {
public:

	// Construct object from given file location and on the given position.
	// Also set current and next direction to neither.
	// If file location isn't set the object won't be loaded and initalized.
	// If pivot point isn't set default one is (0,0).
	MovableObject(std::string location = "", Coordinate<int> pivotPoint = Coordinate<int>());

	// Virtual destructor
	virtual ~MovableObject();

	// Enumarations
	enum class Direction { LEFT, RIGHT, UP, DOWN, NEITHER };

	// Set next direction which will object trying to move until succeed.
	MovableObject& setNextDirection(Direction direction);

	// Set object speed.
	MovableObject& setSpeed(float speed);

	// Get current object direction.
	Direction getCurrentDirection() const { return _currentDirection; }

	// Get next object direction.
	Direction getNextDirection() const { return _nextDirection; }

	// Update object by moving it in current direction and swaping current direction with next direction.
	virtual MovableObject& update();

protected:

	// Data members
	float _speed;
	Direction _currentDirection;
	Direction _nextDirection;
	float _moveAccumulation;

	// Move object in given direction by given amount.
	void move(Direction, int step);

	// Get opposite direction of given one.
	Direction getOppositeDirection(Direction);

};