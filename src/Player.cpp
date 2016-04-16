#include "Player.h"
#include "Graphics.h"


Player::Player(int x, int y){
	this->x = x;
	this->y = y;
}

void Player::draw(Game *game){
	game->graphics.addToScreen(x, y, "@");
}