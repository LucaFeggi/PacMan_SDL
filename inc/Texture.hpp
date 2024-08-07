#pragma once
// Copied from https://lazyfoo.net/tutorials/SDL/ and adapted to my project
#include "main.hpp"
class LTexture {
  public:
    LTexture();
    ~LTexture();
    bool loadFromFile(std::string path);
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor, bool IsLittle = 0);
    void free();
    void setColor(uint8_t red, uint8_t green, uint8_t blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(uint8_t alpha);
    void render(short x = 0, short y = 0, unsigned char facing = 0, SDL_Rect* clip = NULL);
    int getWidth();
    int getHeight();

  private:
    SDL_Texture* mTexture;
    unsigned short mWidth;
    unsigned short mHeight;
};