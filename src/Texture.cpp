#include "Texture.hpp"

LTexture::LTexture() {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture() {
    free();
}

bool LTexture::loadFromFile(std::string path) {
    // Get rid of preexisting texture
    free();
    
    path = build_path + path;
    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        } else {
            // Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    // Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, bool IsLittle) {
    // Get rid of preexisting texture
    free();

    // Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(IsLittle ? LittleFont : Font, textureText.c_str(), textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        // Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (mTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        } else {
            // Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
    // Return success
    return mTexture != NULL;
}

void LTexture::free() {
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor(uint8_t red, uint8_t green, uint8_t blue) {
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(uint8_t alpha) {
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(short x, short y, unsigned char facing, SDL_Rect* clip) {
    // Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    // Set clip rendering dimensions
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    // Render to screen
    SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, facing * 90.0f, NULL, SDL_FLIP_NONE);
}

int LTexture::getWidth() {
    return mWidth;
}

int LTexture::getHeight() {
    return mHeight;
}
