#pragma once
#include <typeinfo>
#include <chrono>
#include <deque>
#include <string>
#include <random>
#include "GameCharacter.h"
#include "Maze.h"

class Ghost : public GameCharacter {
	friend class GhostBehavior;
	friend class GhostHomeMode;
	friend class GhostHomeExitMode;
	friend class GhostHuntingMode;
	friend class GhostShadowHuntingMode;
	friend class GhostScatterMode;
	friend class GhostHomeReturnMode;

public:

	// Construct object from given file location and on the given place and position.
	// If file location isn't set the object won't be loaded and initalized.
	// If pivot point isn't set default one is (0,0).
	// Reference on place where to construct the object must be set.
	Ghost(Maze& place, std::string location = "", Coordinate<int> pivotPoint = Coordinate<int>(0, 0));

	// Virtual destructor
	virtual ~Ghost();

	// Update ghost by moving it in current direction and swaping active animation's model accordingly.
	// Also plans the next move.
	virtual Ghost& update() final;

};


class GhostBehavior : public GameCharacterBehavior {
public:

	// Constructor
	GhostBehavior();

	// Virtual Destructor
	virtual ~GhostBehavior();

	// Pure virtual method
	virtual GhostBehavior& planNextMove(GameCharacter& character) = 0;

protected:

	// Data members
	//Coordinate<int> _oppositeWallPosition;


	// Convert given direction to string representation of ghost's animation. 
	virtual std::string convertToGhostsAnimationName(Ghost::Direction direction);

	// Choose direction randomly depending on the current direction and retrun it.
	// The opposite direction will only be choosen if no other direction is possible.
	virtual Ghost::Direction chooseDirection(Ghost& ghost);

};


class GhostHomeExitMode : public GhostBehavior {
public:

	// Create behavior mode and initalize ghost's moving directions, animation and speed.
	GhostHomeExitMode(Ghost& ghost);

	// Virtual Destructor
	virtual ~GhostHomeExitMode();

	// Choose next move direction or behavior.
	virtual GhostHomeExitMode& planNextMove(GameCharacter& character) final;

private:

	// Choose direction that will bring ghost closer to ghost's home entry point and retrun it.
	virtual Ghost::Direction chooseDirection(Ghost& ghost);

};


class GhostHomeMode : public GhostBehavior {
public:

	// Create behavior mode and initalize ghost's moving directions, animation and speed.
	GhostHomeMode(Ghost& ghost);

	// Virtual destructor
	virtual ~GhostHomeMode();

	// Choose next move direction or behavior.
	virtual GhostHomeMode& planNextMove(GameCharacter& character) final;

private:

	// Choose direction same as current and return it.
	// If can't choose same direction retrun opposite one.
	Ghost::Direction chooseDirection(Ghost&);

};


class GhostHomeReturnMode : public GhostBehavior {
public:

	// Constructor
	GhostHomeReturnMode(Ghost& ghost);

	// Virtual destructor
	virtual ~GhostHomeReturnMode();

	virtual GhostHomeReturnMode& planNextMove(GameCharacter& character) final;

private:

	std::deque<Ghost::Direction> _pathToHome;
	bool _enteringHome;

	virtual std::string convertToGhostsAnimationName(Ghost::Direction direction);

};


class GhostHuntingMode : public GhostBehavior {
public:

	// Create behavior mode and initalize ghost's moving directions, animation and speed.
	GhostHuntingMode(Ghost& ghost);

	// Virtual destructor
	virtual ~GhostHuntingMode();

	// Choose next move direction or behavior.
	virtual GhostHuntingMode& planNextMove(GameCharacter& character) final;

private:

	// Data members
	bool _chasingPacman;
	bool _seeingNextDirection;
	Coordinate<int> _lastSeenPacmanPosition;

	// Look for Pacman between ghost and opposite wall. 
	// If Pacman is found ghost will chase Pacman and copy his moves while seeing him.
	virtual void lookForPacman(Ghost& ghost);

};


class GhostScatterMode : public GhostBehavior {
public:

	// Create behavior mode and initalize ghost's moving directions, animation and speed.
	// Also initialize data members.
	GhostScatterMode(Ghost& ghost, unsigned modeLenght);

	// Virtual Destructor
	virtual ~GhostScatterMode();

	// Choose next move direction or behavior.
	virtual GhostScatterMode& planNextMove(GameCharacter& character) final;

private:

	// Data memebers 
	bool _escapingPacman;
	unsigned _modeLenght;
	unsigned _animationLenght;
	unsigned const _timeBetweenAnimations = 10;
	unsigned const _nAnimationSwitch = 3;
	unsigned const _timeBeforeEnd = _timeBetweenAnimations * 2 * _nAnimationSwitch;

	// Look for Pacman between ghost and opposite wall.
	// If Pacman is found ghost will escape pacman and set next direction to oppsite.
	void lookForPacman(Ghost& ghost);

};