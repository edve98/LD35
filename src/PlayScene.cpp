#include "PlayScene.h"
#include "Input.h"
#include "Room.h"


PlayScene::PlayScene(Game *game) : player(0, 0) , room(80, 30, 3){
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
	room.draw(game, true);
	player.draw(game);
}