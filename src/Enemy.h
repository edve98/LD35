#ifndef ENEMY_H
#define ENEMY_H


#include "Player.h"


class Enemy{
	
	private:
		
		int hitPwr;
		int health;
		
		bool goX = true;
	
	public:
		int x, y;
		
		void totallyNotConstructor(int hitPwr, int health);
		void step(Player *player);
	
};

#endif
