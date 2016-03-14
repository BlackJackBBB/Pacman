#include "Object.h"
#include "Parser.h"


Object::Object(std::string location, Coordinate<int> pivotPoint) : 
	_pivotPoint(pivotPoint)
{
	if (location != "") {
		loadData(location);
		initialize();
	}
}


Object::~Object() {
	for (auto& it : _animations) {
		delete it;
	}
}


Object& Object::loadData(std::string location) {
	std::ifstream file(location);
	if (!file) exit(1);              //exception

	Parser parser;
	std::vector<std::string> animationsPaths;

	parser.parseObject(file, _name, _width, _height, _boundingBoxes, animationsPaths);

	for (auto &it : animationsPaths) {
		_animations.push_back(new Animation(it));
	}

	return *this;
}


Object& Object::initialize() {
	if (!_animations.empty()) _currentAnimation = _animations.begin();
	return *this;
}


Object& Object::setAnimation(std::string animationName) {
	for (std::vector<Animation*>::const_iterator it = _animations.cbegin(); it != _animations.cend(); it++) {
		if ((*it)->getName() == animationName) {
			_currentAnimation = it;
			(*_currentAnimation)->initialize();
			return *this;
		}
	}

	return *this;
}


Object& Object::setPivotPoint(const Coordinate<int>& pivotPoint) {
	_pivotPoint = pivotPoint;
	return *this;
}


bool Object::isOverlaping(const std::vector<Box>& boundingBoxes, const Coordinate<int>& pivotPoint) {
	for (const auto& i : _boundingBoxes) {
		for (const auto& j : boundingBoxes) {
			if ((i.getPivotPoint().getX() + _pivotPoint.getX()) < (j.getPivotPoint().getX() + pivotPoint.getX() + j.getWidth()) &&
				(i.getPivotPoint().getX() + _pivotPoint.getX() + i.getWidth()) > (j.getPivotPoint().getX() + pivotPoint.getX()) &&
				(i.getPivotPoint().getY() + _pivotPoint.getY()) < (j.getPivotPoint().getY() + pivotPoint.getY() + j.getHeight()) &&
				(i.getPivotPoint().getY() + _pivotPoint.getY() + i.getHeight()) > (j.getPivotPoint().getY() + pivotPoint.getY()))
				return true;
		}
	}
	return false;
}


bool Object::isOverlaping(const std::vector<Object*>& objects) {
	for (const auto& object : objects) {
		if (isOverlaping(object->getBoundingBoxes(), object->getPivotPoint())) return true;
	}
	return false;
}