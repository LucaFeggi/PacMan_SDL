#pragma once
#include "Ghost.hpp"
#include "Pac.hpp"
#include "Position.hpp"

class Clyde : public Ghost {
  public:
    Clyde();
    void CalculateTarget(Position mPac);
    void UpdatePos(unsigned char ActualBoard[], Pac& mPac, bool TimedStatus);
};
