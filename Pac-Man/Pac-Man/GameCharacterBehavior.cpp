#include "GameCharacter.h"


GameCharacterBehavior::GameCharacterBehavior() {}


GameCharacterBehavior::~GameCharacterBehavior() {}


GameCharacterBehavior& GameCharacterBehavior::findOppositeWallPosition(GameCharacter& character) {
	Coordinate<int> backup = character._pivotPoint;

	if (character._currentDirection == GameCharacter::Direction::NEITHER) return *this;;

	while (character._pivotPoint.getX() <= character._currentPlace->getWidth() + character.getWidth() && character._pivotPoint.getX() >= -character.getWidth() &&
		character._pivotPoint.getY() <= character._currentPlace->getHeight() + character.getHeight() && character._pivotPoint.getY() >= -character.getHeight() &&
		!character.isOverlaping(character._currentPlace->getGhostsHome().getBoundingBoxes(), character._currentPlace->getGhostsHome().getPivotPoint()) &&
		!character.isOverlaping(character._currentPlace->getStaticObjects())) {
		character.move(character._currentDirection, 1);
	}
	_oppositeWallPosition = character._pivotPoint;

	character._pivotPoint = backup;
	return *this;
}