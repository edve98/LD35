#include "MenuScene.h"
#include "Input.h"
#include "Graphics.h"


MenuScene::MenuScene(Game *game, HelpScene *helpScene, PlayScene *playScene){
	this->game = game;
	this->helpScene = helpScene;
	this->playScene = playScene;
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
				game->setScene(playScene);
				break;
			case 1:
				game->setScene(helpScene);
				break;
			case 2:
				game->quit();
				break;
		}
	}
}


void MenuScene::draw(){
	if(highlightedMenuItem == 0) game->graphics.setFormat(Format::NEGATIVE);
	game->graphics.addToScreen(0, 2, "Play");
	game->graphics.resetFormat();
	
	if(highlightedMenuItem == 1) game->graphics.setFormat(Format::NEGATIVE);
	game->graphics.addToScreen(0, 1, "Help");
	game->graphics.resetFormat();
	
	if(highlightedMenuItem == 2) game->graphics.setFormat(Format::NEGATIVE);
	game->graphics.addToScreen(0, 0, "Quit");
	game->graphics.resetFormat();
}