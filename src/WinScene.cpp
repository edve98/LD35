#include "WinScene.h"
#include "Game.h"
#include "MenuScene.h"
#include "Input.h"
#include "Graphics.h"
#include <fstream>
#include "string"


WinScene::WinScene(Game *game){
	this->game = game;
}


void WinScene::update(){
	if(game->input.isButtonDown(Keyboard::ENTER)){
		game->setScene(menuScene);
	}
}


void WinScene::draw(){
	game->graphics.setCameraCoordinates(0, 0);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 4, game->graphics.getTerminalSizeY() / 2 +3, "You won!");
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 9, game->graphics.getTerminalSizeY() / 2 + 2, "Your score was: " + std::to_string(scoreDisplay));
	if(oldHighscore < scoreDisplay) game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 11, game->graphics.getTerminalSizeY() / 2 + 0, "Last highscore was: " + std::to_string(oldHighscore));
	else game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 12, game->graphics.getTerminalSizeY() / 2 + 0, "Current highscore is: " + std::to_string(oldHighscore));
	if(oldHighscore < scoreDisplay) game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 16, game->graphics.getTerminalSizeY() / 2 - 3, "You just have set the highscore!");
	
	// back button
	game->graphics.setFormat(Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 2, game->graphics.getTerminalSizeY() / 2 - 7, "Back");
	game->graphics.unsetFormat(Format::NEGATIVE);
}


void WinScene::readHighscore(){
	std::ifstream in(".score");
	in >> oldHighscore;
}


void WinScene::writeHighscore(){
	std::ofstream out(".score");
	out << scoreDisplay;
}


void WinScene::newOpen(){
	readHighscore();
	if(oldHighscore < scoreDisplay) writeHighscore();
}
