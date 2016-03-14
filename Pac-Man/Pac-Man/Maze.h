#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include "GhostsHome.h"
#include "Coordinate.h"

class GameCharacter;
class GhostsHome;

class Maze {
public:

	// Construct object from given file location and on the given position.
	// Also create ghost's home.
	// If file location isn't set the object won't be loaded and initalized.
	// If pivot point isn't set default one is (0,0).
	Maze(std::string location = "", Coordinate<int> pivotPoint = Coordinate<int>());

	// Destroy maze and all it's static objects, including ghost's home.
	~Maze();

	// Load data from given file location.
	Maze& loadData(const std::string location);

	// Set maze's pivot point.
	Maze& setPivotPoint(const Coordinate<int>& pivotPoint);

	// Register given character in the maze by it's name. 
	// Characters with same name can't be in the maze in the same time.
	Maze& registerCharacter(GameCharacter& character);

	// Deregister given character from maze by it's name.
	Maze& deregisterCharacter(GameCharacter& character);

	// Remove pallet from maze on the given position.
	Maze& removePallet(Coordinate<int> position);

	// Remove power pallet from maze on the given position.
	Maze& removePowerPallet(Coordinate<int> position);

	// Get reference to pivot point.
	const Coordinate<int>& getPivotPoint() const { return _pivotPoint; }

	// Get reference to pivot point of the object with the given name.
	const Coordinate<int>& getObjectPivotPoint(std::string objectName) const { return _objectsInfo.at(objectName); }

	// Get reference to static objects container.
	const std::vector<Object*>& getStaticObjects() const { return _staticObjects; }

	// Get reference to characters container.
	const std::unordered_map<std::string, const GameCharacter*>& getCharacters() const { return _characters; }

	// Get reference to pallets container.
	const std::unordered_map<Coordinate<int>, Object*>& getPallets() const { return _pallets; }

	// Get reference to power pallets container.
	const std::unordered_map<Coordinate<int>, Object*>& getPowerPallets() const { return _powerPallets; }

	// Get reference to the character with the given name.
	const GameCharacter& getCharacter(std::string objectName) const { return *_characters.at(objectName); }

	// Get reference to the ghost's home.
	GhostsHome& getGhostsHome() const { return *_ghostsHome; }

	// Check if pallet is on the given position.
	bool isPallet(Coordinate<int> position);

	// Check if power pallet is on the given position.
	bool isPowerPallet(Coordinate<int> position);

	// Get maze's width.
	int getWidth() const { return _width; }

	// Get maze's height.
	int getHeight() const { return _height; }

private:

	// Data members
	std::string _name;
	Coordinate<int> _pivotPoint;
	int _width;
	int _height;
	std::unordered_map<std::string, Coordinate<int>> _objectsInfo;
	std::vector<Object*> _staticObjects;
	std::unordered_map<Coordinate<int>, Object*> _pallets;
	std::unordered_map<Coordinate<int>, Object*> _powerPallets;
	std::unordered_map<std::string, const GameCharacter*> _characters;
	GhostsHome* _ghostsHome;

};

