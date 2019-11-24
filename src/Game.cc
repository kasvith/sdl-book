#include "Game.h"

#include <SDL_image.h>
#include <iostream>

Game::Game() {
  m_bRunning = false;
  m_pWindow = nullptr;
  m_pRenderer = nullptr;
  m_x = 100;
}

Game::~Game() {}

bool Game::init(const char *title, const int xpos, const int ypos,
                const int width, const int height, const int flags) {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    m_pWindow =
        SDL_CreateWindow("Welcome to SDL", xpos, ypos, width, height, flags);

    if (m_pWindow) {
      std::cout << "Window creation successfull" << std::endl;
      m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

      if (m_pRenderer) {
        std::cout << "Renderer creation successfull" << std::endl;
        SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
      } else {
        std::cout << "Render init failed" << std::endl;
        return false;
      }
    } else {
      std::cout << "Window init failed" << std::endl;
      return false;
    }
  } else {
    std::cout << "SDL init failed" << std::endl;
    return false;
  }

  L = luaL_newstate();
  luaopen_base(L);
  luaopen_package(L);
  
  luaL_dofile(L, "assets/test.lua");

  if (!TextureManager::Instance().load("assets/animate-alpha.png", "animate",
                                       m_pRenderer)) {
    return false;
  };

  std::cout << "SDL init successfull" << std::endl;
  m_bRunning = true;

  return m_bRunning;
}

void Game::render() {
  SDL_RenderClear(m_pRenderer); // clear screen

  TextureManager::Instance().draw("animate", 0, 0, 128, 82, m_pRenderer);
  TextureManager::Instance().drawFrame("animate", m_x, 100, 128, 82, 1,
                                       m_currentFrame, m_pRenderer);

  SDL_RenderPresent(m_pRenderer); // render screen
}

void Game::clean() {
  lua_close(L);
  std::cout << "Cleaning SDL" << std::endl;
  SDL_DestroyWindow(m_pWindow);
  SDL_DestroyRenderer(m_pRenderer);
  SDL_Quit();
}

void Game::handleEvents() {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      m_bRunning = false;
      break;
    default:
      break;
    }
  }
}

void Game::update() { m_currentFrame = int(((SDL_GetTicks() / 100) % 6)); m_x += 1;
}

