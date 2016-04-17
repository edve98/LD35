#include "Enemy.h"
#include "Player.h"
#include <unistd.h>


void Enemy::totallyNotConstructor(int hitPwr, int health){
	this->hitPwr = hitPwr;
	this->health = health;
}


void Enemy::step(Player *player){
	
	// hit player
	if( ( (x-1 == player->x || x+1 == player->x) && y == player->y ) || ( x == player->x && (y-1 == player->y || y+1 == player->y) ) ){
		player->health--;
	}
	else{ // go near player
		bool didStep = false;
		
		for(int tries = 0; !didStep; tries++){ // TODO: check for collisions
			if(goX){
				if(x < player->x){ // x++
					x++;
					didStep = true;
				}
				else if(x > player->x){ // x--
					x--;
					didStep = true;
				}
			}
			else{
				if(y < player->y){ // y++
					y++;
					didStep = true;
				}
				else if(y > player->y){ // y--
					y--;
					didStep = true;
				}
			}
			goX != goX;
		}
		
	}
	if( ( (x-1 == player->x || x+1 == player->x) && y == player->y ) || ( x == player->x && (y-1 == player->y || y+1 == player->y) ) ){
		player->health--;
	}
	usleep(50000);
}
