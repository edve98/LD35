#include "PlayScene.h"
#include "Input.h"
#include "Room.h"
#include "stdio.h"


PlayScene::PlayScene(Game *game) : player(55, 25){
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
	
	if(cam){ // canter camera on player
		game->graphics.setCameraCoordinates(player.x - game->graphics.getTerminalSizeX() / 2, player.y - game->graphics.getTerminalSizeY() / 2);
		cam = false;
	}
	
	// align camera x
	if(game->graphics.getTerminalSizeX() / 4 * 3 < player.x - game->graphics.getCameraX()){
		game->graphics.updateCameraCoordinates(1, 0);
	}
	if(game->graphics.getTerminalSizeX() / 4 > player.x - game->graphics.getCameraX()){
		game->graphics.updateCameraCoordinates(-1, 0);
	}
	
	// align camera y
	if(game->graphics.getTerminalSizeY() / 4 * 3 < player.y - game->graphics.getCameraY()){
		game->graphics.updateCameraCoordinates(0, 1);
	}
	if(game->graphics.getTerminalSizeY() / 4 > player.y - game->graphics.getCameraY()){
		game->graphics.updateCameraCoordinates(0, -1);
	}
	
	
	lastRoom->draw(game, false);
	currentRoom->draw(game, true);
	player.draw(game);
}