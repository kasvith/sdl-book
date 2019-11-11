#include "TextureManager.h"
#include <iostream>

bool TextureManager::load(std::string filename, std::string id,
                          SDL_Renderer *pRenderer) {
  // Create a temp surface to load the image
  SDL_Surface *pTempSurface = IMG_Load(filename.c_str());

  // error loading the image
  if (!pTempSurface) {
    std::cerr << "Error Loading: " << filename << std::endl;
    return false;
  }

  // create a texture from image
  SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
  SDL_FreeSurface(pTempSurface);

  // error creating the texture
  if (!pTexture) {
    std::cerr << "Texture creation failed for: " << filename << std::endl;
    return false;
  }

  m_textureMap[id] = pTexture;
  return true;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height,
                          SDL_Renderer *pRenderer, SDL_RendererFlip flip) {

  SDL_Rect srcRect, destRect;
  srcRect.x = srcRect.y = 0;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0,
                   flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width,
                               int height, int currentRow, int currentFrame,
                               SDL_Renderer *pRenderer, SDL_RendererFlip flip) {
  SDL_Rect srcRect, destRect;
  srcRect.x = width * currentFrame;
  srcRect.y = height * (currentRow - 1);

  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0,
                   flip);
}
