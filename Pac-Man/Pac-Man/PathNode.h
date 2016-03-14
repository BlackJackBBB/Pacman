#pragma once
#include <functional>
#include "Coordinate.h"

class PathNode {
public:

	// Constructor
	explicit PathNode(const Coordinate<int> position);
	PathNode(const PathNode& node);

	// Destructor
	~PathNode();

	// Get f score of the node.
	float getFScore() const { return _fScore; }

	// Get g score of the node.
	float getGScore() const { return _gScore; }

	// Get pointer to the parrent node.
	PathNode* getParrentNode() const { return _parrent; }

	// Get reference to coordinate of the node.
	const Coordinate<int>& getPosition() const { return _position; }
	
	// Set g score of the node.
	// Also recalculate f score.
	PathNode& setGScore(float value);

	// Set h score of the node. 
	// Also recalculate f score.
	PathNode& setHScore(float value);

	// Set pointer on the parrent node with given parrent's node.
	PathNode& setParentNode(PathNode* node);

private:

	Coordinate<int> _position;

	float _fScore;
	float _gScore;
	float _hScore;
	PathNode* _parrent;
	
	// Recalculate f score by summing g and h score.
	inline void recalculateFScore() { _fScore = _gScore + _hScore; }

};
