#pragma once
#include <functional>

template <class T>
class Coordinate {
public:

	// Construct 2d coordinate of standard type T with  parameters x and y.
	// If any of parameters isn't set default value is choosen.
	// Default values: x = 0, y = 0.
	Coordinate(T x = 0, T y = 0);

	// Destroy object
	~Coordinate();

	// Set value of x coordinate.
	Coordinate& setX(T value);

	// Set value of y coordinate
	Coordinate& setY(T value);

	// Get value of x coordinate.
	T getX() const { return _x; }

	// Get value of y coorinate.
	T getY() const { return _y; }

	// Move coordinate left by value.
	Coordinate& moveLeft(T value);

	// Move coordinate right by value.
	Coordinate& moveRight(T value);

	// Move coorinate up by value.
	Coordinate& moveUp(T value);

	// Move coordinate down by value.
	Coordinate& moveDown(T value);

	// Increase x and y coordinate by value.
	Coordinate& operator+= (T value);

	// Decrease x and y coordinate by value.
	Coordinate& operator-= (T value);

	// Multiply x and y coordinate by value.
	Coordinate& operator*= (T value);

	// Find if coordinate is between two coordinates. 
	// If not return false.
	bool isBetween(const Coordinate<T>& first, const Coordinate<T>& second) const { return (getDistance(first) + getDistance(second)) == first.getDistance(second); }
	
	// Get distance of given coordinate.
	float getDistance(const Coordinate<T>& coordinate) const { return static_cast<float>(std::sqrt(std::pow(coordinate._x - _x, 2) + std::pow(coordinate._y - _y, 2))); }

private:

	// Data memebers
	T _x;
	T _y;

};


template<class T>
struct std::hash<Coordinate<T>> {
	size_t operator() (const Coordinate<T> key) const {
		size_t x = hash<T>()(key.getX());
		size_t y = hash<T>()(key.getY());
		return static_cast<size_t>((500 + x) * 500 + y);
	}
};


////////////////////////////////// Member functions ///////////////////////////////////////


template<class T>
Coordinate<T>::Coordinate(T x, T y) : 
	_x(x),
	_y(y) 
{}


template<class T>
Coordinate<T>::~Coordinate() {}


template<class T>
Coordinate<T>& Coordinate<T>::operator+= (T value) {
	_x += value;
	_y += value;
	return *this;
}


template<class T>
Coordinate<T>& Coordinate<T>::operator-= (T value) {
	_x -= value;
	_y -= value;
	return *this;
}


template<class T>
Coordinate<T>& Coordinate<T>::operator*= (T value) {
	_x *= value;
	_y *= value;
	return *this;
}


template<class T>
Coordinate<T>& Coordinate<T>::setX(T value) {
	_x = value;
	return *this;
}


template<class T>
Coordinate<T>& Coordinate<T>::setY(T value) {
	_y = value;
	return *this;
}


template<class T>
Coordinate<T>& Coordinate<T>::moveLeft(T value) {
	_x -= value;
	return *this;
}


template<class T>
Coordinate<T>& Coordinate<T>::moveRight(T value) {
	_x += value;
	return *this;
}


template<class T>
Coordinate<T>& Coordinate<T>::moveUp(T value) {
	_y += value;
	return *this;
}


template<class T>
Coordinate<T>& Coordinate<T>::moveDown(T value) {
	_y -= value;
	return *this;
}


//////////////////////////////// Non member functions /////////////////////////////////////


template<class T>
Coordinate<T> operator+ (const Coordinate<T>& operand1, const Coordinate<T>& operand2) {
	Coordinate<T> result(operand1.getX() + operand2.getX(), operand1.getY() + operand2.getY());
	return result;
}


template<class T>
Coordinate<T> operator+ (const Coordinate<T>& operand, T value) {
	Coordinate<T> result(operand.getX() + value, operand.getY() + value);
	return result;
}


template<class T>
Coordinate<T> operator- (const Coordinate<T>& operand1, const Coordinate<T>& operand2) {
	Coordinate<T> result(operand1.getX() - operand2.getX(), operand1.getY() - operand2.getY());
	return result;
}


template<class T>
Coordinate<T> operator- (const Coordinate<T>& operand, T value) {
	Coordinate<T> result(operand.getX() - value, operand.getY() - value);
	return result;
}


template<class T>
Coordinate<T> operator* (const Coordinate<T>& operand, T value) {
	Coordinate<T> result(operand.getX() * value, operand.getY() * value);
	return result;
}


template<class T>
bool operator== (const Coordinate<T>& operand1, const Coordinate<T>& operand2) {
	return (operand1.getX() == operand2.getX() && operand1.getY() == operand2.getY());
}


template<class T>
bool operator!= (const Coordinate<T>& operand1, const Coordinate<T>& operand2) {
	return !(operand1 == operand2);
}


template<class T>
bool operator> (const Coordinate<T>& operand1, const Coordinate<T>& operand2) {
	if (operand1.getX() + operand1.getY() == operand2.getX() + operand2.getY()) {
		if (operand1.getX() > operand2.getX()) return true;
		else return false;
	}
	else return operand1.getX() + operand1.getY() > operand2.getX() + operand2.getY();
}


template<class T>
bool operator< (const Coordinate<T>& operand1, const Coordinate<T>& operand2) {
	if (operand1.getX() + operand1.getY() == operand2.getX() + operand2.getY()) {
		if (operand1.getX() < operand2.getX()) return true;
		else return false;
	}
	else return operand1.getX() + operand1.getY() < operand2.getX() + operand2.getY();
}


template<class T>
bool operator<= (const Coordinate<T>& operand1, const Coordinate<T>& operand2) {
	return operand1 < operand2 || operand1 == operand2;
}


template<class T>
bool operator>= (const Coordinate<T>& operand1, const Coordinate<T>& operand2) {
	return operand1 > operand2 || operand1 == operand2;
}