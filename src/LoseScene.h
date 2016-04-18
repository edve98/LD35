#ifndef LOSESCENE_H
#define LOSESCENE_H


#include "Scene.h"
#include "Game.h"


class MenuScene;


class LoseScene : public Scene{
	
	private:
		Game *game;
		int oldHighscore;

	public:
		int scoreDisplay;
		
		Scene *menuScene;
		LoseScene(Game *game);
		void update();
		void draw();
		void readHighscore();
		void newOpen();
	
};

#endif