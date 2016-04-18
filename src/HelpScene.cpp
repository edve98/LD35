#include "HelpScene.h"
#include "Input.h"
#include "string.h"


HelpScene::HelpScene(Game *game){
	this->game = game;
}


void HelpScene::update(){
	if(game->input.isButtonDown(Keyboard::UP_ARROW) && highlightedMenuItem > 0){
		highlightedMenuItem--;
	}
	else if(game->input.isButtonDown(Keyboard::DOWN_ARROW) && highlightedMenuItem < 2){
		highlightedMenuItem++;
	}
	else if(game->input.isButtonDown(Keyboard::ENTER)){
		switch(highlightedMenuItem){
			case 0:
				if(info == 0) info++;
				break;
			
			case 1:
				if(info == 1) info--;
				break;
			
			case 2:
				game->setScene(sceneToReturnTo);
				break;
			
		}
	}
}


void HelpScene::draw(){
	
	switch(info){
		
		case 0:
			game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX() / 2 - 12, game->graphics.getCameraY() + 14, "Use arrows to move around");
			game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX() / 2 - 13, game->graphics.getCameraY() + 13, "Use numpad numbers to shoot");
			game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX() / 2 - 26, game->graphics.getCameraY() + 12, "You shoot into direction the number is from number 5");
			game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX() / 2 - 16, game->graphics.getCameraY() + 11, "Press h to show this help screen");
			game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX() / 2 - 16, game->graphics.getCameraY() + 10, "Press q to close game (and lose)");
			break;
		
		case 1:
			game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX() / 2 - 15, game->graphics.getCameraY() + 14, "You look like this           @");
			game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX() / 2 - 15, game->graphics.getCameraY() + 13, "Doors look like this         #");
			game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX() / 2 - 15, game->graphics.getCameraY() + 12, "Enemies look like this       O");
			game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX() / 2 - 15, game->graphics.getCameraY() + 11, "Dead enemies look like this  _");
			game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX() / 2 - 15, game->graphics.getCameraY() + 10, "          Good luck!          ");
			break;
	}
	
	if(highlightedMenuItem == 0) game->graphics.setFormat(Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX() / 2 - 2, game->graphics.getCameraY() + 7, "Next");
	game->graphics.resetFormat();
	
	if(highlightedMenuItem == 1) game->graphics.setFormat(Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX() / 2 - 4, game->graphics.getCameraY() + 5, "Previous");
	game->graphics.resetFormat();
	
	if(highlightedMenuItem == 2) game->graphics.setFormat(Format::NEGATIVE);
	game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX() / 2 - 2, game->graphics.getCameraY() + 3, "Back");
	game->graphics.resetFormat();
}
