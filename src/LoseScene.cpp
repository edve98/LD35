#include "LoseScene.h"
#include "Game.h"
#include "MenuScene.h"
#include "Input.h"
#include "Graphics.h"
#include <fstream>
#include <string>


LoseScene::LoseScene(Game *game){
	this->game = game;
}


void LoseScene::update(){
	if(game->input.isButtonDown(Keyboard::ENTER)){
		game->setScene(menuScene);
	}
}


void LoseScene::draw(){
	game->graphics.setCameraCoordinates(0, 0);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 4, game->graphics.getTerminalSizeY() / 2 + 4, "You lost");
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 9, game->graphics.getTerminalSizeY() / 2 + 2, "Your score was: " + std::to_string(scoreDisplay));
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 12, game->graphics.getTerminalSizeY() / 2 + 0, "Current highscore is: " + std::to_string(oldHighscore));
	if(oldHighscore < scoreDisplay) game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 21, game->graphics.getTerminalSizeY() / 2 - 3, "Too bad, you would have set the highscore!");
	
	// back button
	game->graphics.setFormat(Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 2, game->graphics.getTerminalSizeY() / 2 - 7, "Back");
	game->graphics.unsetFormat(Format::NEGATIVE);
}


void LoseScene::readHighscore(){
	std::ifstream in(".score");
	in >> oldHighscore;
}


void LoseScene::newOpen(){
	readHighscore();
}