#include "PlayScene.h"
#include "Input.h"
#include "Room.h"
#include "stdio.h"


PlayScene::PlayScene(Game *game) : player(20, 20){
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
	
	if(currentRoom->enterDoor(player)){
		Room *tempRoom = lastRoom;
		lastRoom = currentRoom;
		if(currentRoom->newRoom){
			printf("New room\n");
			currentRoom = new Room(currentRoom->Doors[0].x, currentRoom->Doors[0].y, currentRoom->doorDir);
		}
		else{
			printf("Last room\n");
			currentRoom = tempRoom;
		}
	}
}


void PlayScene::draw(){
	lastRoom->draw(game, false);
	currentRoom->draw(game, true);
	player.draw(game);
}