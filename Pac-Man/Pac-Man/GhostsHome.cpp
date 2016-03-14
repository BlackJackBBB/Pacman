#include "GhostsHome.h"
#include "Maze.h"


GhostsHome::GhostsHome(Maze& place, std::string location, Coordinate<int> pivotPoint) :
	Object(location, pivotPoint)
{
	if (location != "") {
		setAnimation("ghosts_home_closed");
	}
	_entrance = place.getObjectPivotPoint("ghosts_home_entrance");
}


GhostsHome::~GhostsHome() {}


GhostsHome& GhostsHome::initialize() {
	setAnimation("ghosts_home_closed");
	return *this;
}


GhostsHome& GhostsHome::open() {
	setAnimation("ghosts_home_opened");
	return *this;
}


GhostsHome& GhostsHome::close() {
	setAnimation("ghosts_home_closed");
	return *this;
}