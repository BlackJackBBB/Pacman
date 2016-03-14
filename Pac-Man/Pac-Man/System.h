#pragma once
#include <string>
#include "GL\freeglut.h"
#include "Window.h"
#include "GameMenu.h"

class System {
public:

	// Destructor.
	~System();

	// Get instance of singleton class object.
	static System& getInstance();

	// Bind OpenGL display function to system.
	static void bindHandleRender();

	// Bind OpenGL reshape function to system.
	static void bindHandleReshape(int, int);

	// Bind OpenGL mouse input function to system.
	static void bindHandleMouseInput(int, int, int, int);

	// Bind OpenGL special key function to system.
	static void bindHandleSpecialKeyInput(int, int, int);

	// Bind OpenGL special key function to system.
	static void bindHandleKeyboardInput(int, int, int);

	// Bind OpenGL idle function to system.
	static void bindHandleIdle();

	// Bind OpenGL timer function to system.
	static void bindHandleTimer(int);
	
	// Create window with given title and initialize it with preferences fom given configuration file location.
	// If no title is given default is "Untitled".
	System& createWindow(std::string preferencesFileLocation, std::string windowTitle = "Untitled");

	// Destroy window.
	System& destroyWindow();

	// Delete current menu and create new one.
	System& changeMenu(Menu* newMenu);

	// Set a window's resolution.
	System& setResolution(int width, int height);

	// Get reference to window.
	const Window& getWindow() const { return *_window; }

	// Get a window scale factor.                               
	float getScaleFactor() const { return _scaleFactor; }           // Treba promijenit

private:
	
	// Constructor.
	System();

	// Data members
	Window* _window;
	Menu* _currentMenu;
	float _scaleFactor;                    //hardkodirano

	// Callback method for OpenGL display function.
	void handleRender();

	// Callback method for OpenGL reshape function.
	void handleReshape(int, int);

	// Callback method for OpenGL mause input function.
	void handleMouseInput(int, int, int, int);

	// Callback method for OpenGL special key function.
	void handleSpecialKeyInput(int, int, int);

	// Callback method for OpenGL keyboard function.
	void handleKeyboardInput(int, int, int);

	// Callback method for OpenGL idle function.
	void handleIdle();

	// Callback method for OpenGL timer function.
	void handleTimer(int);

	// Initialize OpenGL renderer.
	void initGLRenderer();

};

