#include "WinScene.h"
#include "Game.h"
#include "MenuScene.h"
#include "Input.h"
#include "Graphics.h"


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
	// back button
}
