#pragma once

#include <Globals.hpp>
#include <Position.hpp>
#include <Texture.hpp>
#include <Timer.hpp>

class Fruit : public Position
{
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
		LTexture FruitTexture;
		Timer FruitTimer;
		Timer ScoreTimer;
		SDL_Rect FruitSpriteClips[FruitFrames];
		unsigned char CurrentFruit;
		unsigned short FruitDuration;
		unsigned char FoodCounter;
};
