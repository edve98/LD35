#include "Room.h"
#include "Game.h"
#include "Graphics.h"
#include "stdlib.h"
#include "time.h"
#include <stdio.h>
#include "Player.h"
#include "Enemy.h"


bool Room::isNearOtherDoor(int x, int y, int n){
	for(int i = 0; i < n; i++){
		if( (x <= Doors[i].x+1 && x >= Doors[i].x-1) &&
		    (y <= Doors[i].y+1 && x >= Doors[i].y-1) ){
			return true;
		}
	}
	
	return false;
}


Room::Room(int entranceX, int entranceY, int direction){
	
	srand(time(NULL));
	width = rand() % (maxWidth + 1 - minWidth) + minWidth;
	height = rand() % (maxHeight + 1 - minHeight) + minHeight;
	newDoors = rand() % (maxNewDoors + 1 - minNewDoors) + minNewDoors;
	enemies = rand() % (maxEnemies + 1 - minEnemies) + minEnemies;
	
	switch(direction){
		
		case 0:
			y2 = entranceY - 1;
			y1 = y2 - height + 1;
			x2 = rand() % width + entranceX;
			x1 = x2 - width + 1;
			break;
		
		case 1:
			x2 = entranceX - 1;
			x1 = x2 - width + 1;
			y2 = rand() % height + entranceY;
			y1 = y2 - height + 1;
			break;
		
		case 2:
			y1 = entranceY + 1;
			y2 = y1 + height - 1;
			x2 = rand() % width + entranceX;
			x1 = x2 - width + 1;
			break;
		
		case 3:
			x1 = entranceX + 1;
			x2 = x1 + width - 1;
			y2 = rand() % height + entranceY;
			y1 = y2 - height + 1;
			break;
		
		default: // first room is always like this
			x1 = 50;
			y1 = 20;
			x2 = 60;
			y2 = 30;
			newDoors = 3;
			enemies = 0;
			break;
	}
	
	Doors[0].x = entranceX;
	Doors[0].y = entranceY;
	Doors[0].dir = direction;
	
	for(int i = 1; i < newDoors + 1; i++){
		int temp = rand() % 2;
		
		if(temp){ // new door will be on x axis wall
			temp = rand() % 2;
			if(temp){
				Doors[i].y = y1 - 1;
				Doors[i].dir  = 2;
			}
			else{
				Doors[i].y = y2 + 1;
				Doors[i].dir  = 0;
			}
			
			int veryTemp = 0;
			do{
				if(veryTemp > 100){
					i--;
					continue;
				}
				veryTemp++;
				temp = rand() % (x2 - x1) + x1;
			} while(isNearOtherDoor(temp, Doors[i].y, i));
			Doors[i].x = temp;
		}
		else{ // new door will be on y axis wall
			temp = rand() % 2;
			if(temp){
				Doors[i].x = x1 - 1;
				Doors[i].dir  = 3;
			}
			else{
				Doors[i].x = x2 + 1;
				Doors[i].dir  = 1;
			}
			
			int veryTemp = 0;
			do{
				if(veryTemp > 100){
					i--;
					continue;
				}
				veryTemp++;
				temp = rand() % (y2 - y1) + y1;
			} while(isNearOtherDoor(Doors[i].x, temp, i));
			Doors[i].y = temp;
		}
	}
	
	//enemy spawning
	for(int i = 0; i < enemies; i++){
		int newX = rand() % ( (x2 - 2) + 1 - (x1 + 2) ) + (x1 + 2);
		int newY = rand() % ( (y2 - 1) + 1 - (y1 + 1) ) + (y1 + 1);
		printf("I is here @ %d %d\n", newX, newY);
		if(isColliding(newX, newY)){
			printf("I is bad\n");
			i--;
			continue;
		}
		else{
			Enemies[i].x = newX;
			Enemies[i].y = newY;
			Enemies[i].totallyNotConstructor(1, 1);
		}
	}
	
	
	printf("Enemy count: %d\n", enemies);
	//printf("x1=%d y1=%d x2=%d y2=%d width=%d height=%d\n", x1, y1, x2, y2, width, height);
}


void Room::draw(Game *game, bool isCurrent){
	if(isCurrent){
		for(int x = x1; x <= x2; x++){
			game->graphics.addToScreen(x, y1-1, "-");
			game->graphics.addToScreen(x, y2+1, "-");
		}
		
		for(int y = y1; y <= y2; y++){
			game->graphics.addToScreen(x1-1, y, "|");
			game->graphics.addToScreen(x2+1, y, "|");
		}
		
		for(int i = 0; i < newDoors+1; i++){
			game->graphics.addToScreen(Doors[i].x,Doors[i].y, "#");
		}
		
		for(int x = x1; x < x2+1; x++){
			for(int y = y1; y < y2+1; y++){
				game->graphics.addToScreen(x, y, ".");
			}
		}
		
		for(int i = 0; i < enemies; i++){
			game->graphics.addToScreen(Enemies[i].x, Enemies[i].y, "O");
		}
	}
	else{
		for(int x = x1; x <= x2; x++){
			game->graphics.addToScreen(x, y1-1, ".");
			game->graphics.addToScreen(x, y2+1, ".");
		}
		
		for(int y = y1; y <= y2; y++){
			game->graphics.addToScreen(x1-1, y, ".");
			game->graphics.addToScreen(x2+1, y, ".");
		}
		
		for(int i = 0; i < newDoors+1; i++){
			game->graphics.addToScreen(Doors[i].x,Doors[i].y, ",");
		}
	}
}


bool Room::enterDoor(Player player){
	for(int i = 0; i < newDoors+1; i++){
		switch (Doors[i].dir) {
			case 0:
				if(player.x == Doors[i].x && player.y > Doors[i].y){
					//printf("still alive\n");
					doorID = i;
					changeFirstDoorTo(doorID);
					doorDir = Doors[0].dir + 2;
					if(doorDir > 3) doorDir -= 4;
					return true;
				}
				break;
			
			case 1:
				if(player.x > Doors[i].x && player.y == Doors[i].y){
					//printf("still alive\n");
					doorID = i;
					changeFirstDoorTo(doorID);
					doorDir = Doors[0].dir + 2;
					if(doorDir > 3) doorDir -= 4;
					return true;
				}
				break;
			
			case 2:
				if(player.x == Doors[i].x && player.y < Doors[i].y){
					//printf("still alive\n");
					doorID = i;
					changeFirstDoorTo(doorID);
					doorDir = Doors[0].dir + 2;
					if(doorDir > 3) doorDir -= 4;
					return true;
				}
				break;
			
			case 3:
				if(player.x < Doors[i].x && player.y == Doors[i].y){
					//printf("still alive\n");
					doorID = i;
					changeFirstDoorTo(doorID);
					doorDir = Doors[0].dir + 2;
					if(doorDir > 3) doorDir -= 4;
					return true;
				}
				break;
		}
	}
	return false;
}


void Room::changeFirstDoorTo(int newFirstDoor){
	if(newFirstDoor != 0) newRoom = true;
	else newRoom = false;
	Door tempDoor = Doors[0];
	Doors[0] = Doors[newFirstDoor];
	Doors[newFirstDoor] = tempDoor;
}


bool Room::isColliding(int x, int y){
	if( (x > x1-1 && x < x2+1) && y == y2+1 && notADoor(x, y)) return true;
	else if( x == x2+1 && (y > y1-1 && y < y2+1) && notADoor(x, y)) return true;
	else if( (x > x1-1 && x < x2+1) && y == y1-1 && notADoor(x, y)) return true;
	else if( x == x1-1  && (y > y1-1 && y < y2+1) && notADoor(x, y)) return true;
	else if(isEnemy(x, y)) return true;
	else return false;
}


int Room::isEnemy(int x, int y){
	for(int i = 0; i < enemies; i++){
		if(Enemies[i].x == x && Enemies[i].y == y) return i+1;
	}
	return 0;
}


bool Room::notADoor(int x, int y){
	for(int i = 0; i < newDoors+1; i++){
		if(x == Doors[i].x && y == Doors[i].y){
			return false;
		}
	}
	return true;
}


void Room::updateEnemies(Player *player){
	printf("Do update\n");
	for(int i = 0; i < enemies; i++){
		Enemies[i].step(player);
	}
}
