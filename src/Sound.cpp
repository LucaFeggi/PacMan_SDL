#include "Sound.hpp"

Sound::Sound() {
    Intro = Mix_LoadWAV(std::string(build_path + "Sounds/Intro.wav").c_str());
    EatFruit = Mix_LoadWAV(std::string(build_path + "Sounds/EatFruit.wav").c_str());
    ExtraLife = Mix_LoadWAV(std::string(build_path + "Sounds/ExtraLife.wav").c_str());
    PacDeath = Mix_LoadWAV(std::string(build_path + "Sounds/PacDeath.wav").c_str());
    GhostDeath = Mix_LoadWAV(std::string(build_path + "Sounds/GhostDeath.wav").c_str());
    ScatterGhost = Mix_LoadWAV(std::string(build_path + "Sounds/ScatterGhost.wav").c_str());
    Waka = Mix_LoadWAV(std::string(build_path + "Sounds/Waka.wav").c_str());
    Mix_Volume(-1, 10);
}

Sound::~Sound() {
    Mix_FreeChunk(Intro);
    Mix_FreeChunk(EatFruit);
    Mix_FreeChunk(ExtraLife);
    Mix_FreeChunk(PacDeath);
    Mix_FreeChunk(GhostDeath);
    Mix_FreeChunk(ScatterGhost);
    Mix_FreeChunk(Waka);
    Intro = NULL;
    EatFruit = NULL;
    ExtraLife = NULL;
    PacDeath = NULL;
    GhostDeath = NULL;
    ScatterGhost = NULL;
    Waka = NULL;
}

void Sound::PlayIntro() {
    Mix_PlayChannel(0, Intro, 0);
}
void Sound::PlayEatFruit() {
    Mix_PlayChannel(1, EatFruit, 0);
}
void Sound::PlayExtraLife() {
    Mix_PlayChannel(2, ExtraLife, 0);
}
void Sound::PlayPacDeath() {
    Mix_PlayChannel(3, PacDeath, 0);
}
void Sound::PlayGhostDeath() {
    Mix_PlayChannel(4, GhostDeath, 0);
}
void Sound::PlayScatterGhost() {
    Mix_PlayChannel(5, ScatterGhost, -1);
}
void Sound::StopScatterGhost() {
    Mix_HaltChannel(5);
}
void Sound::PlayWaka() {
    Mix_PlayChannel(6, Waka, -1);
}
void Sound::StopWaka() {
    Mix_HaltChannel(6);
}