#pragma once
#include "main.hpp"

class Sound {
  public:
    Sound();
    ~Sound();
    void PlayIntro();
    void PlayEatFruit();
    void PlayExtraLife();
    void PlayPacDeath();
    void PlayGhostDeath();
    void PlayScatterGhost();
    void StopScatterGhost();
    void PlayWaka();
    void StopWaka();

  private:
    Mix_Chunk* Intro;
    Mix_Chunk* EatFruit;
    Mix_Chunk* ExtraLife;
    Mix_Chunk* PacDeath;
    Mix_Chunk* GhostDeath;
    Mix_Chunk* ScatterGhost;
    Mix_Chunk* Waka;
};
