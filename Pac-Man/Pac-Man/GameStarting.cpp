#include "GameMenu.h"


GameStarting::GameStarting(GameMenu& game) {
	game._pacman->changeBehavior(new PacmanLivingMode(*game._pacman)).setVitalStatus(Ghost::Status::ALIVE).setPivotPoint(game._maze->getObjectPivotPoint(game._pacman->getName()));
	game._redGhost->changeBehavior(new GhostHuntingMode(*game._redGhost)).setVitalStatus(Ghost::Status::ALIVE).setPivotPoint(game._maze->getObjectPivotPoint("ghosts_home_entrance"));
	game._pinkGhost->changeBehavior(new GhostHomeMode(*game._pinkGhost)).setVitalStatus(Ghost::Status::ALIVE).setPivotPoint(game._maze->getObjectPivotPoint("ghosts_home_position_2"));
	game._cyanGhost->changeBehavior(new GhostHomeMode(*game._cyanGhost)).setVitalStatus(Ghost::Status::ALIVE).setPivotPoint(game._maze->getObjectPivotPoint("ghosts_home_position_1"));
	game._orangeGhost->changeBehavior(new GhostHomeMode(*game._orangeGhost)).setVitalStatus(Ghost::Status::ALIVE).setPivotPoint(game._maze->getObjectPivotPoint("ghosts_home_position_3"));
}


GameStarting::~GameStarting() {}


GameStarting& GameStarting::renderScreen(Menu& menu) {
	GameMenu& game = dynamic_cast<GameMenu&>(menu);
	
	game._renderer->clearColorBuffer();

	game.renderMap();
	game.renderPallets();
	game._renderer->
		renderObject(game._orangeGhost->getActiveModel(), game._orangeGhost->getPivotPoint() + game._maze->getPivotPoint() + game._orangeGhost->getWidth() / 2).
		renderObject(game._cyanGhost->getActiveModel(), game._cyanGhost->getPivotPoint() + game._maze->getPivotPoint() + game._cyanGhost->getWidth() / 2).
		renderObject(game._pinkGhost->getActiveModel(), game._pinkGhost->getPivotPoint() + game._maze->getPivotPoint() + game._pinkGhost->getWidth() / 2).
		renderObject(game._redGhost->getActiveModel(), game._redGhost->getPivotPoint() + game._maze->getPivotPoint() + game._redGhost->getWidth() / 2).
		renderObject(game._pacman->getActiveModel(), game._pacman->getPivotPoint() + game._maze->getPivotPoint() + game._pacman->getWidth() / 2, game._pacman->getCurrentDirection());
	game._renderer->renderText("GET READY", Coordinate<int>(System::getInstance().getWindow().getWidth() / 2, System::getInstance().getWindow().getHeight() / 2));

	game._renderer->swapBuffers();
	return *this;
}


GameStarting& GameStarting::updateScreen(Menu& menu) {
	GameMenu& game = dynamic_cast<GameMenu&>(menu);

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	game.changeGameState(new GamePlaying());

	return *this;
}