#pragma once
#include <vector>
#include <string>
#include "Model.h"

class Animation {
public:

	// Create and initialize animation from file location.
	// If file location isn't set, animation won't be loaded.
	Animation(std::string location = "");

	// Destructor
	~Animation();
	
	// Reset animation to initial state.
	// Set active animations's model to first model.
	Animation& initialize();

	// Load animation's data from file location.
	Animation& loadData(std::string location);

	// Get constant reference to animation's current model.
	const Model& getCurrentModel() const { return *(*_currentModel); }

	// Get animation's name.
	std::string getName() const { return _name; }

	// Get number of models in animation.
	size_t getNumberOfModels() const { return _models.size(); }

	// Set current animation's model to next one.
	Animation& switchNextModel();

	// Set direction of model switching to opposite. 
	Animation& switchModelIterationDirection();

private:

	// Animation's model switching direction enumeration.
	enum class Direction { FORWARD, BACKWARD };

	// Data memebers
	std::string _name;
	std::vector<Model*> _models;
	std::vector<Model*>::const_iterator _currentModel;
	Direction _currentIterationDirection;

};

