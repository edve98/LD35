#ifndef PLAYSCENE_H
#define PLAYSCENE_H


#include "Scene.h"
#include "Game.h"


class PlayScene : public Scene{
	
	private:
		Game *game;
	
	public:
		PlayScene(Game *game);
		void update();
		void draw();
	
};

#endif