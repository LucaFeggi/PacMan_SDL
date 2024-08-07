#pragma once
#include "Ghost.hpp"
#include "Pac.hpp"
#include "Position.hpp"

class Inky : public Ghost {
  public:
    Inky();
    void CalculateTarget(Entity mPac, Position mBlinky);
    void UpdatePos(unsigned char ActualBoard[], Pac& mPac, Position mBlinky, bool TimedStatus);
};
