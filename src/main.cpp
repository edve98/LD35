#include "Game.h"
#include "MenuScene.h"

int main(){
	Game game;
  MenuScene menuScene(&game);
  game.setScene(&menuScene);
  game.loop();
	return 0;
}