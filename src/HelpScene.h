#ifndef HELPSCENE_H
#define HELPSCENE_H


#include "Scene.h"
#include "Game.h"
#include "string.h"


class HelpScene : public Scene{
	
	private:
		Game *game;
		int highlightedMenuItem = 0;
		int info = 0;
	
	public:
		Scene *sceneToReturnTo;
		HelpScene(Game *game);
		void update();
		void draw();
	
};

#endif