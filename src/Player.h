#ifndef PLAYER_H
#define PLAYER_H


#include "Game.h"
#include "Graphics.h"


class Player{
	
	public:
		int x, y;
		int health = 10;
		
		Player(int x, int y);
		void draw(Game *game);
	
};

#endif