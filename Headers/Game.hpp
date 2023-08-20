#pragma once

#include <Board.hpp>
#include <Sound.hpp>
#include <Timer.hpp>

#include <Fruit.hpp>
#include <Pac.hpp>
#include <Blinky.hpp>
#include <Inky.hpp>
#include <Pinky.hpp>
#include <Clyde.hpp>

#include <vector>

class Game
{
	public:
		Game();
		~Game();
		void ResetGhostsLifeStatement();
		void ResetGhostsFacing();
		void Start();
		void ModStartStatement(bool NewStartStatement);
		void Clock();
		void UpdatePositions(std::vector<unsigned char> &mover, bool TimedStatus);
		void Food();
		void EntityCollisions();
		void Update(std::vector<unsigned char> &mover);
		unsigned short GetLevel();
		void IncreaseLevel();
		void UpdateDifficulty();
		bool IsLevelCompleted();
		void ClearMover(std::vector<unsigned char> &mover);
	    void DeadlyPacGhostColl();
		void DeadlyGhostPacColl(Ghost &mGhost);
		void ModToWaka(bool NewWaka);
		void DeathSound();
		void ModDeathSoundStatement(bool NewDeathSoundStatement);
		void DrawLittleScore();
		bool Process(Timer &GameTimer, std::vector<unsigned char> &mover, unsigned short &StartTicks);
		void Draw();
		Sound mSound;
	private:
		Board mBoard;
		Pac mPac;
		Blinky mBlinky;
		Inky mInky;
		Pinky mPinky;
		Clyde mClyde;
		Fruit mFruit;
		Timer MapAnimationTimer;
		LTexture Ready;
		LTexture GameOverTexture;
		unsigned char ActualMap[BoardHeight * BoardWidth];
		bool IsGameStarted;
		Timer GhostTimer;
		unsigned short ScatterTime;
		unsigned short ChasingTime;
		unsigned short GhostTimerTarget;
		bool TimedStatus;
		unsigned short Scorer;
		std::vector<Timer> LittleScoreTimer;
		std::vector<Position> LittleScorePositions;
		std::vector<unsigned short> LittleScoreScorers;
		unsigned short LittleTimerTarget;
		unsigned short Level;
		bool IsToScatterSound;
		bool IsToWakaSound;
		Timer WakaTimer;
		bool IsToDeathPacSound;
		unsigned char DeadGhostsCounter;
};
