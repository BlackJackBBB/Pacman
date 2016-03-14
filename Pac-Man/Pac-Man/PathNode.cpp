#include "PathNode.h"


PathNode::PathNode(const Coordinate<int> position) :
	_fScore(0),
	_gScore(0),
	_hScore(0),
	_position(position)
{}


PathNode::PathNode(const PathNode& node) {
	_fScore = node._fScore;
	_gScore = node._gScore;
	_hScore = node._hScore;
	_position = node._position;
	_parrent = node._parrent;
}


PathNode::~PathNode() {}


PathNode& PathNode::setGScore(float value) {
	_gScore = value;
	recalculateFScore();
	return *this;
}


PathNode& PathNode::setHScore(float value) {
	_hScore = value;
	recalculateFScore();
	return *this;
}


PathNode& PathNode::setParentNode(PathNode* node) {
	_parrent = node;
	return *this;
}