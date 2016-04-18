class MenuScene;
class HelpScene;
class PlayScene;
class LoseScene;
class WinScene;

#include "Game.h"
#include "MenuScene.h"
#include "HelpScene.h"
#include "PlayScene.h"
#include "LoseScene.h"
#include "WinScene.h"


int main(){
	Game game;
	
	HelpScene helpScene(&game);
	LoseScene loseScene(&game);
	WinScene winScene(&game);
  MenuScene menuScene(&game, &helpScene, &loseScene, &winScene);
	
	loseScene.menuScene = &menuScene;
	winScene.menuScene = &menuScene;
	
  game.setScene(&menuScene);
  game.loop();
	return 0;
}