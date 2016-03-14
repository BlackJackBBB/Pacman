#pragma once
#include "GL\freeglut.h"
#include "Renderer.h"

class Menu {
	friend class MenuState;

public:

	// Constructors
	Menu();

	// Virtual destructor
	virtual ~Menu();

	// Render and update screen;
	virtual void handleRender();

	// Pure virtual methods
	virtual void handleReshape(int, int) = 0;
	virtual void handleMouseInput(int, int, int, int) = 0;
	virtual void handleSpecialKeyInput(int, int, int) = 0;
	virtual void handleKeyboardInput(int, int, int) = 0;
	virtual void handleIdle() = 0;
	virtual void handleTimer(int) = 0;

	// Set new menu state and delete old one.
	Menu& changeGameState(MenuState* state);

protected:
	
	Renderer* _renderer;
	MenuState* _state;

};


class MenuState {
public:

	// Constructor
	MenuState();

	// Virtual destructor
	~MenuState();

	// Pure virtual functions
	virtual MenuState& renderScreen(Menu& menu) = 0;

	virtual MenuState& updateScreen(Menu& menu) = 0;

};