#include "System.h"
#include "Parser.h"
#include <fstream>


System::System() {
}


System& System::getInstance() {
	static System* getInstance = new System();
	return *getInstance;
}


void System::bindHandleRender() {
	System::getInstance().handleRender();
}


void System::bindHandleReshape(int width, int height) {
	System::getInstance().handleReshape(width, height);
}


void System::bindHandleMouseInput(int button, int state, int x, int y) {
	System::getInstance().handleMouseInput(button, state, x, y);
}


void System::bindHandleSpecialKeyInput(int key, int x, int y) {
	System::getInstance().handleSpecialKeyInput(key, x, y);
}


void System::bindHandleKeyboardInput(int key, int x, int y) {
	System::getInstance().handleKeyboardInput(key, x, y);
}


void System::bindHandleIdle() {
	 System::getInstance().handleIdle();
}


void System::bindHandleTimer(int millis) {
	System::getInstance().handleTimer(millis);
}


void System::handleRender() {
	_currentMenu->handleRender();
}


void System::handleReshape(int width, int height) {
	if (width != _window->getWidth() || height != _window->getHeight()) {
		glutReshapeWindow(_window->getWidth(), _window->getHeight());
	}
	else {
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, width, 0, height);
	}
}


void System::handleMouseInput(int button, int state, int x, int y) {
	_currentMenu->handleMouseInput(button, state, x, y);
}


void System::handleSpecialKeyInput(int key, int x, int y) {
	_currentMenu->handleSpecialKeyInput(key, x, y);
}


void System::handleKeyboardInput(int key, int x, int y) {
	_currentMenu->handleKeyboardInput(key, x, y);
}


void System::handleIdle() {
	_currentMenu->handleIdle();
}


void System::handleTimer(int millis) {
	_currentMenu->handleTimer(millis);
}


inline void System::initGLRenderer() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_FLAT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}


System& System::createWindow(std::string preferencesFileLocation, std::string windowTitle) {
	std::ifstream file(preferencesFileLocation);

	if (!file) exit(1);  //exception

	Parser parser;
	int width, height;
	parser.parseConfigurationFile(file, width, height);
	_scaleFactor = (float) width / 640;

	if (width > 0 && width < 4096 && height > 0 && height < 4096) {
		_window = new Window(width, height, windowTitle);
	}
	initGLRenderer();
	_currentMenu = new GameMenu();

	return *this;
}


System& System::destroyWindow() {
	delete _window;
	return *this;
}


System& System::changeMenu(Menu* newMenu) {
	delete _currentMenu;
	_currentMenu = _currentMenu;
	return *this;
}


System& System::setResolution(int width, int height) {
	_window->setHeight(height).setWidth(width);
	_scaleFactor = (float)width / 640;
	return *this;
}