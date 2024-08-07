#pragma once
#include "Position.hpp"
#include "Texture.hpp"
#include "Timer.hpp"
#include "main.hpp"

class Fruit : public Position {
  public:
    Fruit();
    ~Fruit();
    void ModCurrentFruit(unsigned short ActualActualLevel);
    void UpdateFoodCounter();
    bool IsEatable();
    unsigned short GetScoreValue();
    void StartScoreTimer();
    void ResetScoreTimer();
    bool CheckDespawn();
    void Despawn();
    void ResetFoodCounter();
    void Draw();

  private:
    const unsigned short ScoreTable[FruitFrames] = {100, 300, 500, 700, 1000, 2000, 3000, 5000};

    LTexture FruitTexture;
    Timer FruitTimer;
    Timer ScoreTimer;
    SDL_Rect FruitSpriteClips[FruitFrames];
    unsigned char CurrentFruit;
    unsigned short FruitDuration;
    unsigned char FoodCounter;
};