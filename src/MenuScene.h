#ifndef MENUSCENE_H
#define MENUSCENE_H


class LoseScene;
class WinScene;


#include "Scene.h"
#include "HelpScene.h"
#include "PlayScene.h"
#include "LoseScene.h"
#include "WinScene.h"
#include "Game.h"


class MenuScene : public Scene{
	
	public:
		Game *game;
		HelpScene *helpScene;
		LoseScene *loseScene;
		WinScene *winScene;
		
		PlayScene *playScene = new PlayScene(game, loseScene, winScene, helpScene);
		int highlightedMenuItem = 0;
		
		MenuScene(Game *gamep, HelpScene *helpScene, LoseScene *loseScene, WinScene *winScene);
		void update();
		void draw();
	
};

#endif