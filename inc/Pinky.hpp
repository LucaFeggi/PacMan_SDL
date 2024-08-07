#pragma once
#include "Ghost.hpp"
#include "Pac.hpp"
#include "Position.hpp"

class Pinky : public Ghost {
  public:
    Pinky();
    void CalculateTarget(Entity mPac);
    void UpdatePos(unsigned char ActualBoard[], Pac& mPac, bool TimedStatus);
};
