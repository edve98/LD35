#ifndef MENUSCENE_H
#define MENUSCENE_H


#include "Scene.h"
#include "HelpScene.h"
#include "PlayScene.h"
#include "Game.h"


class PlayScene;


class MenuScene : public Scene{
	
	private:
		Game *game;
		HelpScene *helpScene;
		PlayScene *playScene;
		int highlightedMenuItem = 0;
	
	public:
		MenuScene(Game *gamep, HelpScene *helpScene, PlayScene *playScene);
		void update();
		void draw();
	
};

#endif