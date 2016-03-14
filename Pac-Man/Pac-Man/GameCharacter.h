#pragma once
#include <deque>
#include "MovableObject.h"
#include "Maze.h"

class GameCharacter : public MovableObject {
	friend class GameCharacterBehavior;

public:

	// Enumarations
	enum class Status { ALIVE, DEAD, HIT };

	// Construct object from given file location in the given place and on the given position.
	// If file location isn't set the object won't be loaded and initalized.
	// If pivot point isn't set default one is (0,0).
	// Reference on place where to construct the object must be set.
	GameCharacter(Maze& place, std::string location = "", Coordinate<int> pivotPoint = Coordinate<int>(0, 0));

	// Virtual destructor deregister character from current place.
	virtual ~GameCharacter();

	// Get character vital status represented by enumaration Status.
	Status getVitalStatus() const { return _vitalStatus; }

	// Set character vital status with enumaration Status.
	GameCharacter& setVitalStatus(Status status) const;

	// Get reference to current ghost's derived behavior class type.
	const type_info& getBehaviorId() const;

	// Change character behavior with new one.
	GameCharacter& changeBehavior(GameCharacterBehavior* behavior);

	virtual GameCharacter& update() = 0;

	virtual void operator()();

protected:
	
	// Data memebers
	Maze* _currentPlace;
	mutable Status _vitalStatus;
	GameCharacterBehavior* _behavior;

	// If a character get out of the screen it will be teleported to the opposite side and will return true.
	bool teleportIfNeeded();

	// The character will try move in given direction. 
	// If character not collide with any static object from place it is retrun true, else return flase.
	bool probeDirection(MovableObject::Direction);

	// Find path to given destination and return path with directions.
	// Method use A* alghorithm with manhattan distance as heuristics.
	// If no path is found method return empty container.
	std::deque<Direction> findPath(const Coordinate<int>& destination);
	
};


class GameCharacterBehavior {
public:

	// Constructor
	GameCharacterBehavior();

	// Destructor
	virtual ~GameCharacterBehavior();

	// Pure virtual method
	virtual GameCharacterBehavior& planNextMove(GameCharacter& character) = 0;

	// Find first next opposite wall and remember it's coordinate.
	GameCharacterBehavior& findOppositeWallPosition(GameCharacter& character);

protected:

	// Data members
	Coordinate<int> _oppositeWallPosition;

};