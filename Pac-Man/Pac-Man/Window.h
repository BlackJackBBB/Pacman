#pragma once
#include <string>

class Window {
public:

	// Create OpenGL window and initalize it with given width, height and title.
	// Default parameter's values: width = 640, height = 360, title = Untitled
	Window(int width = 640, int height = 360, std::string title = "Untitled");

	// Destroy window.
	~Window();

	// Set window's width.
	Window& setWidth(int width);

	// Set window's height.
	Window& setHeight(int height);

	// Get window's width.
	int getWidth() const { return _width; }

	// Get window's height.
	int getHeight() const { return _height; }

	// Get window's aspect ratio.
	float getAspectRatio() const { return _aspectRatio; }
	
private:

	// Data memebers
	int _width;
	int _height;
	int _id;
	float _aspectRatio;
	std::string _title;

	// Recalculate and set aspect ratio based on window's current width and height.
	inline void recalculateAspectRatio() { _aspectRatio = (float)_width / (float)_height; }
};

