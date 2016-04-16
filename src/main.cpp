#include "Game.h"
#include "MenuScene.h"
#include "HelpScene.h"
#include "PlayScene.h"


int main(){
	Game game;
	
	HelpScene helpScene(&game);
	PlayScene playScene(&game);
  MenuScene menuScene(&game, &helpScene, &playScene);
	
  game.setScene(&menuScene);
  game.loop();
	return 0;
}