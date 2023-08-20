#pragma once

#include <Ghost.hpp>

class Inky : public Ghost
{
	public:
		Inky();
		void CalculateTarget(Entity mPac, Position mBlinky);
		void UpdatePos(unsigned char ActualBoard[], Pac &mPac, Position mBlinky, bool TimedStatus);
};
