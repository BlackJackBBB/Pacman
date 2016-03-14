#include "Animation.h"
#include "Parser.h"
#include <fstream>


Animation::Animation(std::string location) :
	_currentIterationDirection(Direction::FORWARD)
{
	if (location != "") {
		loadData(location).initialize();
	}
}


Animation::~Animation() {
	for (auto& it : _models) {
		delete it;
	}
}


Animation& Animation::initialize() {
	if (!_models.empty()) _currentModel = _models.begin();
	return *this;
}


Animation& Animation::loadData(std::string location) {
	std::ifstream file(location);
	if (!file) exit(0);              //exception

	Parser parser;
	std::vector<std::string> modelsPaths;

	parser.parseAnimation(file, _name, modelsPaths);

	for (auto &it : modelsPaths) {
		_models.push_back(new Model(it));
	}

	file.close();
	return *this;
}


Animation& Animation::switchNextModel() {
	switch (_currentIterationDirection) {
	case Direction::FORWARD:
		if ((_currentModel + 1) == _models.end()) _currentModel = _models.begin();
		else _currentModel++;
		break;
	case Direction::BACKWARD:
		if (_currentModel == _models.begin()) _currentModel = _models.end() - 1;
		else _currentModel--;
		break;
	default:
		break;
	}

	return *this;
}


Animation& Animation::switchModelIterationDirection() {
	switch (_currentIterationDirection) {
	case Direction::FORWARD:
		_currentIterationDirection = Direction::BACKWARD;
		break;
	case Direction::BACKWARD:
		_currentIterationDirection = Direction::FORWARD;
		break;
	default:
		break;
	}

	return *this;
}