#ifndef MENUSCENE_H
#define MENUSCENE_H


#include "Scene.h"
#include "Game.h"


class MenuScene : public Scene{
	
	private:
		Game *game;
	
	public:
		MenuScene(Game *game);
		void update();
		void draw();
	
};

#endif