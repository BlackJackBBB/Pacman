#pragma once
#include <typeinfo>
#include "GameCharacter.h"

class Pacman : public GameCharacter {
	friend class PacmanBehavior;
	friend class PacmanDyingMode;
	friend class PacmanLivingMode;

public:
	
	// Construct object from given file location and on the given place and position.
	// If file location isn't set the object won't be loaded and initalized.
	// If pivot point isn't set default one is (0,0).
	// Reference on place where to construct the object must be set.
	Pacman(Maze& place, std::string location = "", Coordinate<int> pivotPoint = Coordinate<int>(0, 0));

	// Destruct object and behavior.
	virtual ~Pacman();

	// Update Pacman by moving it in current direction and swaping active animation's model accordingly.
	virtual Pacman& update() final;

	// Get number of eaten pallets (pac-dots).
	unsigned getNumberOfEatenPallets() const { return _nEatenPallets; }

	// Check if Pacman is having power pallet.
	bool isHavingPowerPallet() const { return _havePowerPallet; }

	// Removes power pallet from Pacman.
	// After that Pacman don't have power pallet.
	Pacman& removePowerPallet();

private:

	// Data memebers
	unsigned _nEatenPallets;
	bool _havePowerPallet;
	
};


class PacmanBehavior : public GameCharacterBehavior {
public:

	// Constructor
	PacmanBehavior();

	// Virtual destructor.
	virtual ~PacmanBehavior();

	// Pure virtual methods.
	virtual PacmanBehavior& planNextMove(GameCharacter& character) = 0;

};


class PacmanDyingMode : public PacmanBehavior {
public:

	// Construct behavior and set pacman's dying animation.
	PacmanDyingMode(Pacman& pacman);

	// Virtual destructor.
	virtual ~PacmanDyingMode();

	// Update Pacman by changing it's active animation's model.
	// When all models are used Pacman will die.
	virtual PacmanDyingMode& planNextMove(GameCharacter& character) final;

private:

	// Data members
	unsigned _modelCounter;

};


class PacmanLivingMode : public PacmanBehavior {
public:

	// Construct behavior and set pacman's living animation. 
	PacmanLivingMode(Pacman& pacman);

	// Virtual destructor.
	virtual ~PacmanLivingMode();

	// Update Pacman by moving it in current direction and switching active animation's model accordingly.
	// Also check for pallets and power pallets and eat them.
	// If Pacman is hit he will change behavior to dying mode.
	virtual PacmanLivingMode& planNextMove(GameCharacter& character) final;

};
