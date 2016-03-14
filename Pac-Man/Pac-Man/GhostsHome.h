#pragma once
#include "Object.h"

class Maze;

class GhostsHome : public Object {
public:

	// Create object from file location on given position. 
	// Also load entrance point location from given place.
	// If file location is vaild set closed home animation.
	GhostsHome(Maze& place, std::string location = "", Coordinate<int> pivotPoint = Coordinate<int>());

	// Virtual destructor
	virtual ~GhostsHome();

	// Intialize ghost's home to starting state.
	virtual GhostsHome& initialize();

	// Get reference to entrance coordinate.
	const Coordinate<int>& getEntrancePoint() const { return _entrance; };

	// Open ghost's home by setting open home animation.
	GhostsHome& open();

	// Close ghost's home by setting close home animation.
	GhostsHome& close();

private:

	// Data members
	Coordinate<int> _entrance;

};