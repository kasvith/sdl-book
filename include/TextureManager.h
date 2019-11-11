#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <map>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

class TextureManager {
private:
  TextureManager() = default;
  ~TextureManager() = default;
  std::map<std::string, SDL_Texture *> m_textureMap;

public:
  static auto &Instance() {
    static TextureManager instance;
    return instance;
  };
  // Methods to block
  TextureManager(const TextureManager &arg) = delete;  // Copy constructor
  TextureManager(const TextureManager &&arg) = delete; // Move constructor
  TextureManager &
  operator=(const TextureManager &arg) = delete; // Assignment operator
  TextureManager &
  operator=(const TextureManager &&arg) = delete; // Move operator

  // load an image
  bool load(std::string filename, std::string id, SDL_Renderer *pRenderer);

  // draw a texture to the renderer
  void draw(std::string id, int x, int y, int width, int height,
            SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

  // draw a frame to screen
  void drawFrame(std::string id, int x, int y, int width, int height,
                 int currentRow, int currentFrame, SDL_Renderer *pRenderer,
                 SDL_RendererFlip flip = SDL_FLIP_NONE);
};

#endif // !__TEXTURE_MANAGER_H__