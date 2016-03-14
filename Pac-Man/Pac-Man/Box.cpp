#include "Box.h"


Box::Box(Coordinate<int> pivotPoint, int width, int height) :
	_pivotPoint(pivotPoint), 
	_width(width),
	_height(height)
{}


Box::~Box() {}


Box& Box::setWidth(int width) {
	_width = width;
	return *this;
}


Box& Box::setHeight(int height) {
	_height = height;
	return *this;
}


Box& Box::setPivotPoint(Coordinate<int> pivotPoint) {
	_pivotPoint = pivotPoint;
	return *this;
}