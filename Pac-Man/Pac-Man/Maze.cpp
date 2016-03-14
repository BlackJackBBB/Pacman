#include "Maze.h"
#include "GameCharacter.h"
#include "Parser.h"


Maze::Maze(std::string location, Coordinate<int> pivotPoint) :
	_pivotPoint(pivotPoint)
{
	if (location != "") {
		loadData(location);
	}
	_ghostsHome = new GhostsHome(*this, "data/objects/ghosts_home/ghosts_home.pob", _objectsInfo.at("ghosts_home"));
}


Maze::~Maze() {
	for (auto& it : _staticObjects) delete it;
	
	delete _ghostsHome;

	for (auto& it : _pallets) delete it.second;

	for (auto& it : _powerPallets) delete it.second;
}


Maze& Maze::loadData(const std::string location) {
	using namespace std;

	ifstream file(location);
	if (!file) exit(1); //exception

	Parser parser;
	vector<pair<string, Coordinate<int>>> objects, pallets, powerPallets;
	parser.parseMaze(file, _name, _width, _height, objects, pallets, powerPallets, _objectsInfo);
	
	for (const auto& it : objects) {
		_staticObjects.push_back(new Object(get<0>(it), get<1>(it)));
	}

	for (const auto& it : pallets) {
		Object* pallet = new Object(get<0>(it), get<1>(it));
		if ((_pallets.emplace(Coordinate<int>(pallet->getPivotPoint().getX() + pallet->getWidth() / 2, pallet->getPivotPoint().getY() + pallet->getHeight() / 2), pallet)).second == false) delete pallet;
	}

	for (const auto& it : powerPallets) {
		Object* pallet = new Object(get<0>(it), get<1>(it));
		if ((_powerPallets.emplace(Coordinate<int>(pallet->getPivotPoint().getX() + pallet->getWidth() / 2, pallet->getPivotPoint().getY() + pallet->getHeight() / 2), pallet)).second == false) delete pallet;
	}

	file.close();
	return *this;
}


Maze& Maze::setPivotPoint(const Coordinate<int>& pivotPoint) {
	_pivotPoint = pivotPoint;
	return *this;
}


Maze& Maze::registerCharacter(GameCharacter& character) {
	_characters.emplace(character.getName(), &character);
	return *this;
}


Maze& Maze::deregisterCharacter(GameCharacter& character) {
	_characters.erase(character.getName());
	return *this;
}


bool Maze::isPallet(Coordinate<int> position) {
	auto element = _pallets.find(position);
	if (element != _pallets.end()) return true;
	else return false;
}


Maze& Maze::removePallet(Coordinate<int> position) {
	auto element = _pallets.find(position);
	if (element != _pallets.end()) {
		delete element->second;
		_pallets.erase(element);
	}
	return *this;
}


bool Maze::isPowerPallet(Coordinate<int> position) {
	auto element = _powerPallets.find(position);
	if (element != _powerPallets.end()) return true;
	else return false;
}


Maze& Maze::removePowerPallet(Coordinate<int> position) {
	auto element = _powerPallets.find(position);
	if (element != _powerPallets.end()) {
		delete element->second;
		_powerPallets.erase(element);
	}
	return *this;
}