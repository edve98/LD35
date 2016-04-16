#include "MenuScene.h"
#include "Input.h"


MenuScene::MenuScene(Game *game){
	this->game = game;
}

void MenuScene::update(){
}

void MenuScene::draw(){
	game->graphics.addToScreen(0, 0, "hello");
}