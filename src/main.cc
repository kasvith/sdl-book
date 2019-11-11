#include <SDL.h>
#include <iostream>

#include "Game.h"

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

Game *g_pGame = 0;
int main(int argc, char *args[]) {
  g_pGame = new Game();

  g_pGame->init("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

  while (g_pGame->isRunning()) {
    g_pGame->handleEvents();
    g_pGame->update();
    g_pGame->render();
  }

  g_pGame->clean();

  return 0;
}