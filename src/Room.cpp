#include "Room.h"
#include "Game.h"
#include "Graphics.h"
#include "stdlib.h"
#include "time.h"
#include <stdio.h>


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
	
	switch(direction){
		
		case 0:
			y2 = entranceY - 1;
			y1 = y2 - height + 1;
			x2 = (rand() % ((entranceX + width - 1) + 1 - entranceX)) + (entranceX);
			x1 = x2 - width + 1;
			break;
		
		case 1:
			x2 = entranceX - 1;
			x1 = x2 - width + 1;
			y2 = (rand() % ((entranceY + height - 1) + 1 - entranceY)) + (entranceY);
			y1 = y2 - height + 1;
			break;
		
		case 2:
			y1 = entranceY + 1;
			y2 = y1 + height - 1;
			x2 = (rand() % ((entranceX + width - 1) + 1 - entranceX)) + (entranceX);
			x1 = x2 - width + 1;
			break;
		
		case 3:
			x1 = entranceX + 1;
			x2 = x1 + width - 1;
			y2 = (rand() % ((entranceY + height - 1) + 1 - entranceY)) + (entranceY);
			y1 = y2 - height + 1;
			break;
		
		default: // first room is always like this
			x1 = 15;
			y1 = 15;
			x2 = 25;
			y2 = 25;
			newDoors = 1;
			break;
	}
	
	Doors[0].x = entranceX;
	Doors[0].y = entranceY;
	
	for(int i = 1; i < newDoors + 1; i++){
		int temp = rand() % 2;
		
		if(temp){ // new door will be on x axis wall
			temp = rand() % 2;
			if(temp) Doors[i].y = y1 - 1;
			else Doors[i].y = y2 + 1;
			
			do{
				temp = rand() % (x2 - x1) + x1;
			} while(isNearOtherDoor(temp, Doors[i].y, i));
			Doors[i].x = temp;
		}
		else{ // new door will be on y axis wall
			temp = rand() % 2;
			if(temp) Doors[i].x = x1 - 1;
			else Doors[i].x = x2 + 1;
			
			do{
				temp = rand() % (y2 - y1) + y1;
			} while(isNearOtherDoor(Doors[i].x, temp, i));
			Doors[i].y = temp;
		}
	}
	
	printf("x1=%d y1=%d x2=%d y2=%d width=%d height=%d\n", x1, y1, x2, y2, width, height);
}


void Room::draw(Game *game, bool isCurrent){
	//if(!isCurrent) game->graphics.setFormat(Format::);
	//game->graphics.setFormat(Format::NEGATIVE);
	
	
	
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
	//game->graphics.unsetFormat(Format::NEGATIVE);
}