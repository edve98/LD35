#include "PlayScene.h"
#include "Input.h"
#include "Room.h"
#include "stdio.h"
#include "string.h"
#include <unistd.h>
#include "LoseScene.h"
#include "HelpScene.h"
#include "WinScene.h"


PlayScene::PlayScene(Game *game, LoseScene *loseScene, WinScene *winScene) : player(55, 25){
	this->game = game;
	this->loseScene = loseScene;
	this->winScene = winScene;
}


void PlayScene::update(){
	if(bulletIsMoving){
		if(currentRoom->isColliding(bulletX + bulletDirX, bulletY + bulletDirY, 0) || currentRoom->isColliding(bulletX, bulletY, 0)){ // explosion
			explosionState++;
			usleep(10000);
			
			if(explosionState < 3){
				usleep(10000);
			}
			else{
				// inflict damage, remove bullet
				//int a = isEnemy(, );
				//if(a) 
				
				if(currentRoom->isEnemy(bulletX + bulletDirX, bulletY + bulletDirY)){
					currentRoom->Enemies[currentRoom->isEnemy(bulletX + bulletDirX, bulletY + bulletDirY)-1].health--;
				}
				if(currentRoom->isEnemy(bulletX, bulletY)){
					currentRoom->Enemies[currentRoom->isEnemy(bulletX, bulletY)-1].health--;
				}
				
				explosionState = 0;
				bulletIsMoving = false;
				
				// after everything is done move enemies
				printf("Call update\n");
				currentRoom->updateEnemies(&player);
			}
		}
		else{ // move bullet
			bulletX += bulletDirX;
			bulletY += bulletDirY;
			usleep(30000);
			if(bulletDirX != 0 && bulletDirY != 0) usleep(30000);
		}
	}
	else{
		bool doShoot = false;
		
		// movement
		if(game->input.isButtonDown(Keyboard::UP_ARROW)){
			if(!currentRoom->isColliding(player.x, player.y+1)){
				player.y++;
				playerMoved = true;
			}
		}
		else if(game->input.isButtonDown(Keyboard::DOWN_ARROW)){
			if(!currentRoom->isColliding(player.x, player.y-1)){
				player.y--;
				playerMoved = true;
			}
		}
		else if(game->input.isButtonDown(Keyboard::LEFT_ARROW)){
			if(!currentRoom->isColliding(player.x-1, player.y)){
				player.x--;
				playerMoved = true;
			}
		}
		else if(game->input.isButtonDown(Keyboard::RIGHT_ARROW)){
			if(!currentRoom->isColliding(player.x+1, player.y)){
				player.x++;
				playerMoved = true;
			}
		}
		// shooting
		else if(game->input.isButtonDown(Keyboard::NUM_8)){
			doShoot = true;
			bulletDirX = 0;
			bulletDirY = 1;
			bulletLooks = '|';
		}
		else if(game->input.isButtonDown(Keyboard::NUM_9)){
			doShoot = true;
			bulletDirX = 1;
			bulletDirY = 1;
			bulletLooks = '/';
		}
		else if(game->input.isButtonDown(Keyboard::NUM_6)){
			doShoot = true;
			bulletDirX = 1;
			bulletDirY = 0;
			bulletLooks = '-';
		}
		else if(game->input.isButtonDown(Keyboard::NUM_3)){
			doShoot = true;
			bulletDirX = 1;
			bulletDirY = -1;
			bulletLooks = '\\';
		}
		else if(game->input.isButtonDown(Keyboard::NUM_2)){
			doShoot = true;
			bulletDirX = 0;
			bulletDirY = -1;
			bulletLooks = '|';
		}
		else if(game->input.isButtonDown(Keyboard::NUM_1)){
			doShoot = true;
			bulletDirX = -1;
			bulletDirY = -1;
			bulletLooks = '/';
		}
		else if(game->input.isButtonDown(Keyboard::NUM_4)){
			doShoot = true;
			bulletDirX = -1;
			bulletDirY = 0;
			bulletLooks = '-';
		}
		else if(game->input.isButtonDown(Keyboard::NUM_7)){
			doShoot = true;
			bulletDirX = -1;
			bulletDirY = 1;
			bulletLooks = '\\';
		}
		if(doShoot){ // do a shoot
			// spawn a bullet and that's it?
			bulletX = player.x + bulletDirX;
			bulletY = player.y + bulletDirY;
			bulletIsMoving = true;
			return;
		}
		
		
		if(playerMoved){
			printf("Call update\n");
			currentRoom->updateEnemies(&player);
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
		
		playerMoved = false;
	}
	
	if(loadLose){ // death
		// TODO: score
		usleep(2000000);
		game->setScene(loseScene);
	}
	
	/*if(player.health < 1){ // win
		// TODO: score
		game->setScene();
	}*/
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
	
	// map
	lastRoom->draw(game, false);
	currentRoom->draw(game, true);
	
	// player
	player.draw(game);
	
	// health
	game->graphics.addToScreen(game->graphics.getCameraX(), game->graphics.getCameraY(), "Your health: ");
	game->graphics.setFormat(Format::BACKGROUND_RED);
	for(int i = 0; i < player.health; i++){
		if(i % 2 == 0) game->graphics.addToScreen(game->graphics.getCameraX() + 13 + i, game->graphics.getCameraY(), ".");
		else game->graphics.addToScreen(game->graphics.getCameraX() + 13 + i, game->graphics.getCameraY(), "`");
	}
	game->graphics.unsetFormat(Format::BACKGROUND_RED);
	
	if(bulletIsMoving){
		game->graphics.addToScreen(bulletX, bulletY, std::string(1, bulletLooks));
	}
	
	switch(explosionState){
		case 1:
			break;
		
		case 2:
			break;
	}
	
	
	if(player.health < 1){ // death
		game->graphics.setFormat(Format::NEGATIVE);
		game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX()/2-7, game->graphics.getCameraY() + game->graphics.getTerminalSizeY()/2 +1, "              ");
		game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX()/2-7, game->graphics.getCameraY() + game->graphics.getTerminalSizeY()/2   , " You are dead ");
		game->graphics.addToScreen(game->graphics.getCameraX() + game->graphics.getTerminalSizeX()/2-7, game->graphics.getCameraY() + game->graphics.getTerminalSizeY()/2 -1, "              ");
		game->graphics.unsetFormat(Format::NEGATIVE);
		loadLose = true;
	}
}