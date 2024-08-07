// Copied from https://lazyfoo.net/tutorials/SDL/ and adapted to my project
#pragma once
#include "stdint.h" 

class Timer {
  public:
    Timer();
    void Start();
    void Reset();
    void Restart();
    void Pause();
    void Unpause();
    uint32_t GetTicks();
    bool isStarted();
    bool isPaused();

  private:
    uint32_t StartTicks;  // Ticks since start
    uint32_t PausedTicks; // Ticks since stop
    bool Paused;
    bool Started;
};
