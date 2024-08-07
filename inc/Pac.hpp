#pragma once
#include "Entity.hpp"
#include "Texture.hpp"
#include "main.hpp"

class Pac : public Entity {
  public:
    Pac();
    ~Pac();
    void UpdatePos(std::vector<Position::Direction>& mover, unsigned char ActualMap[]);
    unsigned char FoodCollision(unsigned char ActualMap[]);
    bool IsEnergized();
    void ChangeEnergyStatus(bool NewEnergyStatus);
    void SetFacing(unsigned char mover);
    bool IsDeadAnimationEnded();
    void ModDeadAnimationStatement(bool NewDeadAnimationStatement);
    void UpdateCurrentLivingPacFrame();
    void ResetCurrentLivingFrame();
    void WallCollisionFrame();
    void Draw();

  private:
    LTexture LivingPac;
    LTexture DeathPac;
    SDL_Rect LivingPacSpriteClips[LivingPacFrames];
    SDL_Rect DeathPacSpriteClips[DeathPacFrames];
    unsigned char CurrLivingPacFrame;
    unsigned char CurrDeathPacFrame;
    bool EnergyStatus;
    bool DeadAnimationStatement;
};
