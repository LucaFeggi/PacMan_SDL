#include "Timer.hpp"
#include "main.hpp"

Timer::Timer() {
    StartTicks = 0;
    PausedTicks = 0;
    Paused = false;
    Started = false;
}

void Timer::Start() {
    Started = true;
    Paused = false;
    StartTicks = SDL_GetTicks();
    PausedTicks = 0;
}

void Timer::Reset() {
    Started = false;
    Paused = false;
    StartTicks = 0;
    PausedTicks = 0;
}

void Timer::Restart() {
    this->Reset();
    this->Start();
}

void Timer::Pause() {
    if (Started && !Paused) {
        Paused = true;
        PausedTicks = SDL_GetTicks() - StartTicks;
        StartTicks = 0;
    }
}

void Timer::Unpause() {
    if (Started && Paused) {
        Paused = false;
        StartTicks = SDL_GetTicks() - PausedTicks;
        PausedTicks = 0;
    }
}

uint32_t Timer::GetTicks() {
    uint32_t time = 0;
    if (Started) {
        if (Paused) {
            time = PausedTicks;
        } else {
            time = SDL_GetTicks() - StartTicks;
        }
    }
    return time;
}

bool Timer::isStarted() {
    return Started;
}

bool Timer::isPaused() {
    return Paused && Started;
}
