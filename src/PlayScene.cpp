#include "PlayScene.h"
#include "Input.h"


PlayScene::PlayScene(Game *game) : player(0, 0){
	this->game = game;
}


void PlayScene::update(){
	if(game->input.isButtonDown(Keyboard::UP_ARROW)){
		player.y++;
	}
	else if(game->input.isButtonDown(Keyboard::DOWN_ARROW)){
		player.y--;
	}
	else if(game->input.isButtonDown(Keyboard::LEFT_ARROW)){
		player.x--;
	}
	else if(game->input.isButtonDown(Keyboard::RIGHT_ARROW)){
		player.x++;
	}
	
}


void PlayScene::draw(){
	player.draw(game);
}
