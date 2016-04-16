#ifndef HELPSCENE_H
#define HELPSCENE_H


#include "Scene.h"
#include "Game.h"


class HelpScene : public Scene{
	
	private:
		Game *game;
	
	public:
		HelpScene(Game *game);
		void update();
		void draw();
	
};

#endif