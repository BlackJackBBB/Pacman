#include "Ghost.h"


GhostBehavior::GhostBehavior() {}


GhostBehavior::~GhostBehavior() {}


std::string GhostBehavior::convertToGhostsAnimationName(Ghost::Direction direction) {
	switch (direction) {
	case Ghost::Direction::LEFT:
		return "ghost_left";
	case Ghost::Direction::RIGHT:
		return "ghost_right";
	case Ghost::Direction::UP:
		return "ghost_up";
	case Ghost::Direction::DOWN:
		return "ghost_down";
	default:
		return "";
	}
}


Ghost::Direction GhostBehavior::chooseDirection(Ghost& ghost) {
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::uniform_int_distribution<int> distribution(1, 3);

	bool left = true;
	bool up = true;
	bool down = true;
	bool right = true;
	switch (ghost._currentDirection) {
	case Ghost::Direction::LEFT:
		while (left || up || down) {
			int direction = distribution(generator);
			switch (direction) {
			case 1:
				if (ghost.probeDirection(Ghost::Direction::LEFT)) return Ghost::Direction::LEFT;
				else left = false;
				break;
			case 2:
				if (ghost.probeDirection(Ghost::Direction::UP)) return Ghost::Direction::UP;
				else up = false;
				break;
			case 3:
				if (ghost.probeDirection(Ghost::Direction::DOWN)) return Ghost::Direction::DOWN;
				else down = false;
				break;
			}
		}
		return Ghost::Direction::RIGHT;
	case Ghost::Direction::RIGHT:
		while (right || up || down) {
			int direction = distribution(generator);
			switch (direction) {
			case 1:
				if (ghost.probeDirection(Ghost::Direction::RIGHT)) return Ghost::Direction::RIGHT;
				else right = false;
				break;
			case 2:
				if (ghost.probeDirection(Ghost::Direction::UP)) return Ghost::Direction::UP;
				else up = false;
				break;
			case 3:
				if (ghost.probeDirection(Ghost::Direction::DOWN)) return Ghost::Direction::DOWN;
				else down = false;
				break;
			}
		}
		return Ghost::Direction::LEFT;
	case Ghost::Direction::UP:
		while (left || up || right) {
			int direction = distribution(generator);
			switch (direction) {
			case 1:
				if (ghost.probeDirection(Ghost::Direction::LEFT)) return Ghost::Direction::LEFT;
				else left = false;
				break;
			case 2:
				if (ghost.probeDirection(Ghost::Direction::UP)) return Ghost::Direction::UP;
				else up = false;
				break;
			case 3:
				if (ghost.probeDirection(Ghost::Direction::RIGHT)) return Ghost::Direction::RIGHT;
				else right = false;
				break;
			}
		}
		return Ghost::Direction::DOWN;
	case Ghost::Direction::DOWN:
		while (left || down || right) {
			int direction = distribution(generator);
			switch (direction) {
			case 1:
				if (ghost.probeDirection(Ghost::Direction::LEFT)) return Ghost::Direction::LEFT;
				else left = false;
				break;
			case 2:
				if (ghost.probeDirection(Ghost::Direction::DOWN)) return Ghost::Direction::DOWN;
				else down = false;
				break;
			case 3:
				if (ghost.probeDirection(Ghost::Direction::RIGHT)) return Ghost::Direction::RIGHT;
				else right = false;
				break;
			}
		}
		return Ghost::Direction::UP;
	case Ghost::Direction::NEITHER:
		distribution = std::uniform_int_distribution<int>(1, 4);
		while (true) {
			int direction = distribution(generator);
			switch (direction) {
			case 1:
				if (ghost.probeDirection(Ghost::Direction::LEFT)) return Ghost::Direction::LEFT;
				break;
			case 2:
				if (ghost.probeDirection(Ghost::Direction::DOWN)) return Ghost::Direction::DOWN;
				break;
			case 3:
				if (ghost.probeDirection(Ghost::Direction::RIGHT)) return Ghost::Direction::RIGHT;
				break;
			case 4:
				if (ghost.probeDirection(Ghost::Direction::UP)) return Ghost::Direction::UP;
				break;
			}
		}
	default:
		return Ghost::Direction::NEITHER;
	}
}
