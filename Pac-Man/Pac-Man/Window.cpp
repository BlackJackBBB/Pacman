#include "Window.h"
#include "GL\freeglut.h"


Window::Window(int width, int height, std::string title) : 
	_width(width), 
	_height(height), 
	_title(title) 
{
	_aspectRatio = (float)width / (float)height;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow(title.c_str());
	_id = glutGetWindow();	
}


Window::~Window() {
	glutDestroyWindow(_id);
}


Window& Window::setWidth(int width) {
	_width = width;
	glutReshapeWindow(_width, _height);
	recalculateAspectRatio();
	return *this;
}


Window& Window::setHeight(int height) {
	_height = height;
	glutReshapeWindow(_width, _height);
	recalculateAspectRatio();
	return *this;
}