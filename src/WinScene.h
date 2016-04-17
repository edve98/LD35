#ifndef WINSCENE_H
#define WINSCENE_H


#include "Scene.h"
#include "WinScene.h"
#include "Game.h"


class MenuScene;


class WinScene : public Scene{
	
	private:
		Game *game;

	public:
		MenuScene *menuScene;
		WinScene(Game *game);
		void update();
		void draw();
	
};

#endif