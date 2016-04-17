#ifndef PLAYER_H
#define PLAYER_H


#include "Game.h"
#include "Graphics.h"


class Player{
	
	private:
		int maxHealth = 10;
	
	public:
		int x, y;
		int health = maxHealth;
		
		Player(int x, int y);
		void draw(Game *game);
	
};

#endif