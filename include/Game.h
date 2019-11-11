#ifndef __GAME_H__
#define __GAME_H__

#include "TextureManager.h"
#include <SDL.h>

class Game {
public:
  Game();
  ~Game();

  bool init(const char *title, const int xpos, const int ypos, const int width,
            const int height, const int flags);
  void render();
  void handleEvents();
  void clean();
  void update();

  inline bool isRunning() { return m_bRunning; }

private:
  SDL_Window *m_pWindow;
  SDL_Renderer *m_pRenderer;

  int m_currentFrame;

  bool m_bRunning;
};
#endif
