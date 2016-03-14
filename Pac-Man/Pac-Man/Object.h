#pragma once
#include <vector>
#include <map>
#include <string>
#include "Coordinate.h"
#include "Animation.h"
#include "Box.h"

class Object {
public:

	// Construct object from given file location and on the given position.
	// If file location isn't set the object won't be loaded and initalized.
	// If pivot point isn't set default one is (0,0).
	Object(std::string location = "", Coordinate<int> pivotPoint = Coordinate<int>(0, 0));

	// Destroy object and all animations.
	virtual ~Object();

	// Initialize object by setting first animation active.
	virtual Object& initialize();

	// Load data from given file location.
	Object& loadData(const std::string location);

	// Set pivot point with given coordinate.
	Object& setPivotPoint(const Coordinate<int>& pivotPoint);

	// Set active animation by giving it's name. 
	Object& setAnimation(std::string animationName);

	// Get object's name.
	std::string getName() const { return _name; }

	// Get reference to object's pivot point.
	const Coordinate<int>& getPivotPoint() const { return _pivotPoint; }

	// Get reference to bounding boxes container.
	const std::vector<Box>& getBoundingBoxes() const { return _boundingBoxes; }

	// Get reference to active model from current animation.
	const Model& getActiveModel() const { return (*_currentAnimation)->getCurrentModel(); }

	// Get reference to current animation.
	const Animation& getCurrentAnimation() const { return *(*_currentAnimation); }

	// Get object's width.
	int getWidth() const { return _width; }

	// Get object's height.
	int getHeight() const { return _height; }

	// Find overlping between object and given bunding boxes.
	// If object overlaps with any of them return true else return false.
	bool isOverlaping(const std::vector<Box>& boundingBoxes, const Coordinate<int>& pivotPoint);

	// Find overlaping between object and given set of ovjects.
	// If object overlaps with any of them return true, else return false.
	bool isOverlaping(const std::vector<Object*>& objects);

protected:

	// Data memebers 
	std::string _name;
	Coordinate<int> _pivotPoint;
	int _width;
	int _height;
	std::vector<Box> _boundingBoxes;
	std::vector<Animation*> _animations;
	std::vector<Animation*>::const_iterator _currentAnimation;

};

