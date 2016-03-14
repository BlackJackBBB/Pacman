#include "GameMenu.h"
#include <thread>


GamePlaying::GamePlaying() :
	gameWin_(false)
{}


GamePlaying::~GamePlaying() {}


GamePlaying& GamePlaying::renderScreen(Menu& menu) {
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
	if (gameWin_) game._renderer->renderText("YOU WON", Coordinate<int>(System::getInstance().getWindow().getWidth() / 2, System::getInstance().getWindow().getHeight() / 2));
	
	game._renderer->swapBuffers();
	return *this;
}


GamePlaying& GamePlaying::updateScreen(Menu& menu) {
	GameMenu& game = dynamic_cast<GameMenu&>(menu);

	std::thread thread1 { std::ref(*game._redGhost) };
	std::thread thread2 { std::ref(*game._pinkGhost) };
	std::thread thread4 { std::ref(*game._cyanGhost) };
	std::thread thread3 { std::ref(*game._orangeGhost) };
	std::thread thread5 { std::ref(*game._pacman) };
	
	/*game._redGhost->update();
	game._pinkGhost->update();
	game._cyanGhost->update();
	game._orangeGhost->update();
	game._pacman->update();*/

	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
	thread5.join();

	if (game._maze->getPallets().size() == 0 && game._maze->getPowerPallets().size() == 0) {
		gameWin_ = true;
		renderScreen(game);
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		exit(1);
	}

	if (game._pacman->getNumberOfEatenPallets() == 20) game._pinkGhost->changeBehavior(new GhostHomeExitMode(*game._pinkGhost));
	if (game._pacman->getNumberOfEatenPallets() == 40) game._cyanGhost->changeBehavior(new GhostHomeExitMode(*game._cyanGhost));
	if (game._pacman->getNumberOfEatenPallets() == 60) game._orangeGhost->changeBehavior(new GhostHomeExitMode(*game._orangeGhost));

	if (game._pacman->isHavingPowerPallet()) {
		if (game._redGhost->getBehaviorId() == typeid(GhostHuntingMode) || game._redGhost->getBehaviorId() == typeid(GhostScatterMode)) game._redGhost->changeBehavior(new GhostScatterMode(*game._redGhost, 300));
		if (game._pinkGhost->getBehaviorId() == typeid(GhostHuntingMode) || game._pinkGhost->getBehaviorId() == typeid(GhostScatterMode)) game._pinkGhost->changeBehavior(new GhostScatterMode(*game._pinkGhost, 300));
		if (game._cyanGhost->getBehaviorId() == typeid(GhostHuntingMode) || game._cyanGhost->getBehaviorId() == typeid(GhostScatterMode)) game._cyanGhost->changeBehavior(new GhostScatterMode(*game._cyanGhost, 300));
		if (game._orangeGhost->getBehaviorId() == typeid(GhostHuntingMode) || game._orangeGhost->getBehaviorId() == typeid(GhostScatterMode)) game._orangeGhost->changeBehavior(new GhostScatterMode(*game._orangeGhost, 300));
		game._pacman->removePowerPallet();
	}

	if (game._pacman->getVitalStatus() == GameCharacter::Status::HIT) {
		game.changeGameState(new GameEnding());
		game._pacman->setAnimation("pacman_dead");
		return *this;
	}
	/*if (game._redGhost->getVitalStatus() == GameCharacter::Status::DEAD) {
		game._redGhost->setVitalStatus(Ghost::Status::ALIVE).setPivotPoint(game._maze->getObjectPivotPoint("ghost_pink"));
		game._redGhost->changeBehavior(new GhostHomeExitMode(*game._redGhost));
	}
	if (game._pinkGhost->getVitalStatus() == GameCharacter::Status::DEAD) {
		game._pinkGhost->setVitalStatus(Ghost::Status::ALIVE).setPivotPoint(game._maze->getObjectPivotPoint("ghost_pink"));
		game._pinkGhost->changeBehavior(new GhostHomeExitMode(*game._pinkGhost));
	}
	if (game._cyanGhost->getVitalStatus() == GameCharacter::Status::DEAD) {
		game._cyanGhost->setVitalStatus(Ghost::Status::ALIVE).setPivotPoint(game._maze->getObjectPivotPoint("ghost_pink"));
		game._cyanGhost->changeBehavior(new GhostHomeExitMode(*game._cyanGhost));
	}
	if (game._orangeGhost->getVitalStatus() == GameCharacter::Status::DEAD) {
		game._orangeGhost->setVitalStatus(Ghost::Status::ALIVE).setPivotPoint(game._maze->getObjectPivotPoint("ghost_pink"));
		game._orangeGhost->changeBehavior(new GhostHomeExitMode(*game._orangeGhost));
	}*/

	return *this;
}