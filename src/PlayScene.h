#ifndef PLAYSCENE_H
#define PLAYSCENE_H


#include "Scene.h"
#include "Game.h"
#include "Player.h"


class PlayScene : public Scene{
	
	private:
		Game *game;
		Player player;
	
	public:
		PlayScene(Game *game);
		void update();
		void draw();
	
};

#endif