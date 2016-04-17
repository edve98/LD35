#include "Enemy.h"
#include "Player.h"
#include <unistd.h>
#include <stdio.h>


void Enemy::totallyNotConstructor(int hitPwr, int health){
	this->hitPwr = hitPwr;
	this->health = health;
}


void Enemy::step(Player *player){
	//printf("Do step\n");
	// hit player
	if( !( ( (x-1 == player->x || x+1 == player->x) && y == player->y ) || ( x == player->x && (y-1 == player->y || y+1 == player->y) ) ) ){
		
		
		// go near player
		bool didStep = false;
		
		for(int tries = 0; didStep == false; tries++){ // TODO: check for collisions
			//printf("isLoop\n");
			if(tries > 10) break;
			
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
					//printf("Hello\n");
					y++;
					didStep = true;
				}
				else if(y > player->y){ // y--
					//printf("Hello\n");
					y--;
					didStep = true;
				}
			}
			goX = !goX;
		}
		
	}
	if( ( (x-1 == player->x || x+1 == player->x) && y == player->y ) || ( x == player->x && (y-1 == player->y || y+1 == player->y) ) ){
		player->health--;
	}
	//usleep(50000);
}
