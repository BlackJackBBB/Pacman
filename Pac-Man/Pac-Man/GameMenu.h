#pragma once
#include <typeinfo>
#include <thread>
#include <chrono>
#include <GL/freeglut.h>
#include "Menu.h"
#include "Pacman.h"
#include "Maze.h"
#include "Ghost.h"
#include "System.h"

class GameMenu : public Menu {
	friend class GameState;
	friend class GameEnding;
	friend class GamePlaying;
	friend class GameStarting;

public:

	// Construct game menu, all game objects and characters.
	// Also set game state to start and initialize other data members.
	GameMenu();

	// Destroy all game objects, characters and game state.
	~GameMenu();

	// Method for handling system's special key input.
	// It handle arrow keys input.
	virtual void handleSpecialKeyInput(int key, int x, int y) final;

	// Method for handling system's timer function.
	// It refresh game screen every given milliseconds.
	virtual void handleTimer(int millis) final;

	// Unused handlers
	virtual void handleReshape(int, int) final {};
	virtual void handleMouseInput(int, int, int, int) final {};
	virtual void handleKeyboardInput(int, int, int) final {}
	virtual void handleIdle() final {}

	/*// Set new game state and delete old one.
	GameMenu& changeGameState(GameState* newState);*/

private:

	// Data members
	Pacman* _pacman;
	Maze* _maze;
	Ghost* _pinkGhost;
	Ghost* _redGhost;
	Ghost* _orangeGhost;
	Ghost* _cyanGhost;
	unsigned short _lives;

	// Render game maze with all is's static subobjects.
	void renderMap();

	// Render pallets and power pallets (Pacman's food) 
	void renderPallets();

};


class GameState : public MenuState {
public:

	// Constructor
	GameState();

	// Virtual destructor
	virtual ~GameState();

	// Pure virtual methods
	virtual GameState& renderScreen(Menu& menu) = 0;

	virtual GameState& updateScreen(Menu& menu) = 0;

};


class GameStarting : public GameState {
public:

	// Construct game state and set game's characters alive and position them to their start postions
	GameStarting(GameMenu& game);

	// Virtual destructor
	virtual ~GameStarting();

	// Render current scene's objects.
	virtual GameStarting& renderScreen(Menu& menu) final;

	// Update current scene's objects.
	virtual GameStarting& updateScreen(Menu& menu) final;

};


class GamePlaying : public GameState {
public:

	// Construct game state and initialize data members.
	GamePlaying();

	// Virtual destructor
	virtual ~GamePlaying();

	// Render current scene's objects.
	virtual GamePlaying& renderScreen(Menu& menu) final;

	// Update current scene's objects.
	virtual GamePlaying& updateScreen(Menu& menu) final;

private:

	// Data members
	bool gameWin_;

};


class GameEnding : public GameState {
public:

	// Construct game state and initialize data members.
	GameEnding();

	// Virtual destructor
	virtual ~GameEnding();

	// Render current scene's objects.
	virtual GameEnding& renderScreen(Menu& menu) final;

	// Update current scene's objects.
	virtual GameEnding& updateScreen(Menu& menu) final;

private:

	// Data members
	bool gameOver_;

};