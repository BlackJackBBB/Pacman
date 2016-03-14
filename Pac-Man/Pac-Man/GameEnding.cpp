#include "GameMenu.h"


GameEnding::GameEnding() :
	gameOver_(false)
{}


GameEnding::~GameEnding() {}


GameEnding& GameEnding::renderScreen(Menu& menu) {
	GameMenu& game = dynamic_cast<GameMenu&>(menu);

	game._renderer->clearColorBuffer();

	game.renderMap();
	game._renderer->renderObject(game._pacman->getActiveModel(), game._pacman->getPivotPoint() + game._maze->getPivotPoint() + game._pacman->getWidth() / 2, game._pacman->getCurrentDirection());
	if (gameOver_) game._renderer->renderText("GAME OVER", Coordinate<int>(System::getInstance().getWindow().getWidth() / 2, System::getInstance().getWindow().getHeight() / 2));

	game._renderer->swapBuffers();
	return *this;
}


GameEnding& GameEnding::updateScreen(Menu& menu) {
	GameMenu& game = dynamic_cast<GameMenu&>(menu);

	game._pacman->update();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	if (game._pacman->getVitalStatus() == Pacman::Status::DEAD) {
		if (game._lives-- != 0) game.changeGameState(new GameStarting(game)); //treba promjnit u gamestartng
		else {
			gameOver_ = true;
			renderScreen(game);
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			exit(1);
		}
	}

	return *this;
}