#pragma once

#include <Ghost.hpp>

class Blinky : public Ghost
{
	public:
		Blinky();
		void CalculateTarget(Position mPac);
		void UpdatePos(unsigned char ActualBoard[], Pac &mPac, bool TimedStatus);
};
