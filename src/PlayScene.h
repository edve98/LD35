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
	
	public:
		PlayScene(Game *game);
		void update();
		void draw();
	
};

#endif