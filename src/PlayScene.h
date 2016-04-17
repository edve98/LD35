#ifndef PLAYSCENE_H
#define PLAYSCENE_H


#include "Scene.h"
#include "Game.h"
#include "Room.h"
#include "Player.h"


class PlayScene : public Scene{
	
	private:
		Game *game;
		Player player;
		Room *lastRoom = new  Room(-10, -10, -1);
		Room *currentRoom = new  Room(-10, -10, -1);
		bool playerMoved = false;
		bool bulletIsMoving = false;
		int bulletDirX = 0, bulletDirY = 0;
		int bulletX, bulletY;
		char bulletLooks = '?'; //TODO add jostShot bool to make enemies step after explosion?
		int explosionState = 0;
	
	public:
		bool cam = true;
		PlayScene(Game *game);
		void update();
		void draw();
	
};

#endif