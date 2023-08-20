#pragma once

#include <Globals.hpp>
#include <Position.hpp>

class Entity : public Position{
	public:
		Entity(EntityType MyIdentity);
		unsigned char GetIdentity();
		unsigned char GetSpeed();
		unsigned char GetDirection();
		unsigned char GetFacing();
		bool IsAlive();
		void ModSpeed(unsigned char NewSpeed);
		void ModDirection(unsigned char NewDirection);
		void ModFacing(unsigned char NewFacing);
		void ModLifeStatement(bool NewLifeStatement);	
		void GetPossiblePosition(short &x, short &y, unsigned char mover);
		void CharBoardPos(unsigned char SideDir, Position &BoardPos, float cell_x, float cell_y);
		bool WallCollision(short x, short y, unsigned char ActualMap[] , bool CanUseDoor = 0);
		void Move(unsigned char mover);
		void CheckWrap();
		bool IsColliding(Position other);
	private:
		unsigned char Identity;
		unsigned char Speed;
		unsigned char Direction;
		unsigned char Facing;
		bool LifeStatement;
};
