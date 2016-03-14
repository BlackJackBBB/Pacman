#include "GameMenu.h"
#include "Renderer.h"


GameMenu::GameMenu() :
	_lives(3)/*,
	_maze(new Maze("data/mazes/google.pmp", Coordinate<int>(0, 85))),
	_pacman(new Pacman(*_maze, "data/objects/pacman/pacman.pob", _maze->getObjectPivotPoint("pacman"))),
	_cyanGhost(new Ghost(*_maze, "data/objects/ghosts/cyan/ghost_cyan.pob", _maze->getObjectPivotPoint("ghosts_home_position_1"))),
	_pinkGhost(new Ghost(*_maze, "data/objects/ghosts/pink/ghost_pink.pob", _maze->getObjectPivotPoint("ghosts_home_position_2"))),
	_orangeGhost(new Ghost(*_maze, "data/objects/ghosts/orange/ghost_orange.pob", _maze->getObjectPivotPoint("ghosts_home_position_3"))),
	_redGhost(new Ghost(*_maze, "data/objects/ghosts/red/ghost_red.pob", _maze->getObjectPivotPoint("ghosts_home_entrance")))*/
{
	_maze = new Maze("data/mazes/google.pmp", Coordinate<int>(0, 85));
	
	_pacman = new Pacman(*_maze, "data/objects/pacman/pacman.pob", _maze->getObjectPivotPoint("pacman"));
	_pacman->setSpeed(1);

	_cyanGhost = new Ghost(*_maze, "data/objects/ghosts/cyan/ghost_cyan.pob", _maze->getObjectPivotPoint("ghosts_home_position_1"));
	_pinkGhost = new Ghost(*_maze, "data/objects/ghosts/pink/ghost_pink.pob", _maze->getObjectPivotPoint("ghosts_home_position_2"));
	_orangeGhost = new Ghost(*_maze, "data/objects/ghosts/orange/ghost_orange.pob", _maze->getObjectPivotPoint("ghosts_home_position_3"));
	_redGhost = new Ghost(*_maze, "data/objects/ghosts/red/ghost_red.pob", _maze->getObjectPivotPoint("ghosts_home_entrance"));
	//_pacman->setSpeed(1);
	_state = new GameStarting(*this);
	
}


GameMenu::~GameMenu() {
	delete _pacman;
	delete _redGhost;
	delete _cyanGhost;
	delete _pinkGhost;
	delete _orangeGhost;
	delete _maze;
	delete _state;
}


void GameMenu::handleSpecialKeyInput(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		_pacman->setNextDirection(Pacman::Direction::LEFT);
		break;
	case GLUT_KEY_RIGHT:
		_pacman->setNextDirection(Pacman::Direction::RIGHT);
		break;
	case GLUT_KEY_UP:
		_pacman->setNextDirection(Pacman::Direction::UP);
		break;
	case GLUT_KEY_DOWN:
		_pacman->setNextDirection(Pacman::Direction::DOWN);
		break;
	default:
		break;
	}
}


void GameMenu::handleTimer(int millis) {
	glutPostRedisplay();
	glutTimerFunc(15, System::bindHandleTimer, 0);
}


void GameMenu::renderMap() {
	for (const auto& object : _maze->getStaticObjects()) {
		_renderer->renderObject(object->getActiveModel(), object->getPivotPoint() + _maze->getPivotPoint());
	}
	_renderer->renderObject(_maze->getGhostsHome().getActiveModel(), _maze->getGhostsHome().getPivotPoint() + _maze->getPivotPoint());
}


void GameMenu::renderPallets() {
	for (const auto& pallet : _maze->getPallets()) {
		_renderer->renderObject(pallet.second->getActiveModel(), pallet.second->getPivotPoint() + _maze->getPivotPoint());
	}
	for (const auto& pallet : _maze->getPowerPallets()) {
		_renderer->renderObject(pallet.second->getActiveModel(), pallet.second->getPivotPoint() + _maze->getPivotPoint());
	}
}