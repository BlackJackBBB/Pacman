#pragma once
#include "Coordinate.h"

class Box {
public:

	// Construct 2d box with parameters pivotPoint, width, height.
	// If any of parameters isn't set default value is choosen.
	// Default values: pivotPoint = (0, 0), width = 1, height = 1.
	Box(Coordinate<int> pivotPoint = Coordinate<int>(0, 0), int width = 1, int height = 1);

	// Destroy box
	~Box();

	// Set box's width.
	Box& setWidth(int width);

	// Set box's height.
	Box& setHeight(int height);

	// Set box's pivot point.
	Box& setPivotPoint(Coordinate<int> pivotPoint);

	// Get value of box's width.
	int getWidth() const { return _width; }

	// Get value of box's height. 
	int getHeight() const { return _height; }

	// Get reference to box's pivot point.
	const Coordinate<int>& getPivotPoint() const { return _pivotPoint; }

private:

	// Data members
	Coordinate<int> _pivotPoint;
	int _width;
	int _height;

};

