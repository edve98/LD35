#include "MenuScene.h"
#include "Input.h"
#include "Graphics.h"
#include "stdio.h"


MenuScene::MenuScene(Game *gamep, HelpScene *helpScene, LoseScene *loseScene, WinScene *winScene){
	this->game = gamep;
	this->helpScene = helpScene;
	this->loseScene = loseScene;
	this->winScene = winScene;
}


void MenuScene::update(){
	
	if(game->input.isButtonDown(Keyboard::UP_ARROW) && highlightedMenuItem > 0){
		highlightedMenuItem--;
	}
	else if(game->input.isButtonDown(Keyboard::DOWN_ARROW) && highlightedMenuItem < 2){
		highlightedMenuItem++;
	}
	else if(game->input.isButtonDown(Keyboard::ENTER)){
		switch(highlightedMenuItem){
			case 0:
				playScene = new PlayScene(game, loseScene, winScene, helpScene); // that did it
				game->setScene(playScene);
				break;
			case 1:
				helpScene->sceneToReturnTo = this;
				game->setScene(helpScene);
				break;
			case 2:
				game->quit();
				break;
		}
	}
}


void MenuScene::draw(){
	game->graphics.setCameraCoordinates(0, 0);
	
	game->graphics.setFormat(Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX()/2-7, game->graphics.getCameraY() + game->graphics.getTerminalSizeY()/2 +3, "              ");
	game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX()/2-7, game->graphics.getCameraY() + game->graphics.getTerminalSizeY()/2 +2, " SYSTEM SHIFT ");
	game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX()/2-7, game->graphics.getCameraY() + game->graphics.getTerminalSizeY()/2 +1, "              ");
	game->graphics.unsetFormat(Format::NEGATIVE);
	
	if(highlightedMenuItem == 0) game->graphics.setFormat(Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 2, game->graphics.getTerminalSizeY() / 2 - 2, "Play");
	game->graphics.resetFormat();
	
	if(highlightedMenuItem == 1) game->graphics.setFormat(Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 2, game->graphics.getTerminalSizeY() / 2 - 4, "Help");
	game->graphics.resetFormat();
	
	if(highlightedMenuItem == 2) game->graphics.setFormat(Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getTerminalSizeX() / 2 - 2, game->graphics.getTerminalSizeY() / 2 - 6, "Quit");
	game->graphics.resetFormat();
}