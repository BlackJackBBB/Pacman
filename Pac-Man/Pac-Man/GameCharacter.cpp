#include "GameCharacter.h"
#include "PathNode.h"
#include <functional>
#include <array>
#include <queue>
#include <unordered_map>


GameCharacter::GameCharacter(Maze& place, std::string location, Coordinate<int> pivotPoint) :
	MovableObject(location, pivotPoint),
	_currentPlace(&place),
	_vitalStatus(Status::ALIVE)
{	
	_currentPlace->registerCharacter(*this);
}


GameCharacter::~GameCharacter() {
	_currentPlace->deregisterCharacter(*this);
}


GameCharacter& GameCharacter::setVitalStatus(Status status) const {
	_vitalStatus = status;
	return const_cast<GameCharacter&>(*this);
}


bool GameCharacter::teleportIfNeeded() {
	if (_pivotPoint.getX() <= -_width + 1) {
		_pivotPoint.setX(_currentPlace->getWidth() - 1);
		return true;
	}
	if (_pivotPoint.getX() >= _currentPlace->getWidth()) {
		_pivotPoint.setX(-_width + 1);
		return true;
	}
	return false;
}


bool GameCharacter::probeDirection(MovableObject::Direction direction) {
	move(direction, 1);
	if (isOverlaping(_currentPlace->getStaticObjects()) || isOverlaping(_currentPlace->getGhostsHome().getBoundingBoxes(), _currentPlace->getGhostsHome().getPivotPoint())) {
		move(getOppositeDirection(direction), 1);
		return false;
	}
	else {
		move(getOppositeDirection(direction), 1);
		return true;
	}
}


std::deque<GameCharacter::Direction> GameCharacter::findPath(const Coordinate<int>& destination) {
	auto nodeLessFunctor = [](const PathNode* a, const PathNode* b) { return a->getFScore() > b->getFScore(); };
	std::priority_queue<PathNode*, std::vector<PathNode*>, decltype(nodeLessFunctor)> open(nodeLessFunctor);
	std::unordered_map<Coordinate<int>, PathNode*> closed;
	std::unordered_map<Coordinate<int>, PathNode*> openMap;
	std::array<Direction, 4> possibleDirections = { Direction::LEFT, Direction::RIGHT, Direction::UP, Direction::DOWN };
	Coordinate<int> source = _pivotPoint;
	bool isFound = false;
	auto heuristicDistance = [](const Coordinate<int>& a, const Coordinate<int>& b) { return abs(a.getX() - b.getX()) + abs(a.getY() - b.getY()); };

	PathNode* first = new PathNode(_pivotPoint);

	open.push(first);
	openMap[first->getPosition()] = first;

	PathNode* currentNode = nullptr;
	while (!open.empty()) {
		currentNode = open.top();

		if (currentNode->getPosition() == destination) {
			isFound = true;
			break;
		}

		open.pop();
		openMap.erase(currentNode->getPosition());
		closed[currentNode->getPosition()] = currentNode;

		_pivotPoint = currentNode->getPosition();
		for (const auto& direction : possibleDirections) {
			if (probeDirection(direction)) {
				move(direction, 1);
				PathNode* adjacentNode = new PathNode(_pivotPoint);
				if (closed.find(adjacentNode->getPosition()) == closed.end()) {
					auto openNode = openMap.find(adjacentNode->getPosition());
					if (openNode == openMap.end()) {
						adjacentNode->setHScore(heuristicDistance(adjacentNode->getPosition(), destination));
						adjacentNode->setGScore(currentNode->getGScore() + 1);       // 1 je jedinièni pomak
						adjacentNode->setParentNode(currentNode);
						open.push(adjacentNode);
						openMap[adjacentNode->getPosition()] = adjacentNode;
						move(getOppositeDirection(direction), 1);
						continue;
					}
					else {
						adjacentNode->setGScore(currentNode->getGScore() + 1);       // 1 je jedinièni pomak
						if (adjacentNode->getGScore() < openNode->second->getGScore()) openNode->second->setGScore(adjacentNode->getGScore()).setParentNode(currentNode);
					}
				}
				delete adjacentNode;
				move(getOppositeDirection(direction), 1);
			}
		}

	}

	std::deque<Direction> path;
	if (isFound) {
		while (currentNode->getPosition() != source) {
			if (currentNode->getPosition().getX() == currentNode->getParrentNode()->getPosition().getX()) {
				if (currentNode->getPosition().getY() > currentNode->getParrentNode()->getPosition().getY()) path.push_front(Direction::UP);
				else path.push_front(Direction::DOWN);
			}
			else if (currentNode->getPosition().getY() == currentNode->getParrentNode()->getPosition().getY()) {
				if (currentNode->getPosition().getX() > currentNode->getParrentNode()->getPosition().getX()) path.push_front(Direction::RIGHT);
				else path.push_front(Direction::LEFT);
			}
			currentNode = currentNode->getParrentNode();
		}
	}

	while (!open.empty()) {
		currentNode = open.top();
		delete currentNode;
		open.pop();
	}

	for (auto it : closed) delete it.second;

	_pivotPoint = source;

	return path;

}


GameCharacter& GameCharacter::changeBehavior(GameCharacterBehavior* behavior) {
	delete _behavior;
	_behavior = behavior;
	return *this;
}


const type_info& GameCharacter::getBehaviorId() const { return typeid(*_behavior); }


void GameCharacter::operator()() {
	update();
}