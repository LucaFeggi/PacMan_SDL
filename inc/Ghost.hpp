#pragma once
#include "Entity.hpp"
#include "Pac.hpp"
#include "Position.hpp"
#include "Texture.hpp"
#include "Timer.hpp"
#include "main.hpp"

class Ghost : public Entity {
  public:
    Ghost(SDL_Color MyColor, EntityType MyIdentity);
    ~Ghost();
    bool IsTargetToCalculate(Pac& mPac);
    void PossDirsBubbleSort(std::vector<float>& Distances, std::vector<unsigned char>& PossibleDirections);
    void CalculateDirection(unsigned char ActualMap[]);
    bool IsHome();
    void ModStatus(bool NewStatus);
    void UpdateStatus(Pac& mPac, bool TimedStatus);
    void UpdateFacing(Pac& mPac);
    void UpdateSpeed(Pac& mPac);
    void Draw(Pac& mPac, Timer mGhostTimer, unsigned short mTimerTarget);
    Position Target;
    Position ScatterTarget;
    Position DoorTarget;
    Position Home;

  private:
    LTexture Body;
    LTexture Eyes;
    SDL_Rect GhostBodySpriteClips[GhostBodyFrames];
    SDL_Rect GhostEyeSpriteClips[GhostEyeFrames];
    SDL_Color Color;
    unsigned char CurrentBodyFrame;
    bool CanUseDoor;
    bool Status; // false -> chase	true -> scatter
};
