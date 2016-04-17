#ifndef ROOM_H
#define ROOM_H


#include "Game.h"
#include "Graphics.h"
#include "vector"
#include "Player.h"
#include "Enemy.h"


struct Door{
	int x, y;
	int dir;
};


class Room{
	
	private:
		// options for random gen
		static const int minWidth = 20;
		static const int maxWidth = 40;
		static const int minHeight = 10;
		static const int maxHeight = 25;
		static const int minNewDoors = 0;
		static const int maxNewDoors = 2;
		static const int minEnemies = 1;
		static const int maxEnemies = 3;
		
		// generated variables for this room
		int width;
		int height;
		int newDoors;
		int enemies;
		
		bool isNearOtherDoor(int x, int y, int n);
		void changeFirstDoorTo(int newFirstDoor);
	
	public:
		// this room
		Door Doors[maxNewDoors + 1];
		Enemy *Enemies = new Enemy[maxEnemies];
		int x1, y1;
		int x2, y2;
		
		// exit variables
		int doorID;
		int doorDir;
		bool newRoom;
		
		Room(int entranceX, int entranceY, int direction);
		void draw(Game *game, bool isCurrent);
		bool enterDoor(Player player);
		bool isColliding(int x, int y);
		int isEnemy(int x, int y); // 0 if not, id+1 if yes
		bool notADoor(int x, int y);
		void updateEnemies(Player *player);
};

#endif