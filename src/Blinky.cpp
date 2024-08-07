#include "Blinky.hpp"

Blinky::Blinky() : Ghost(Red, EntityType::eBlinky) {
    this->ScatterTarget.ModCoords(25 * BlockSize24 + BlockSize24 / 2, BlockSize24 / 2);
    this->Home.ModCoords(13 * BlockSize24 + BlockSize24 / 2, 17 * BlockSize24 + BlockSize24 / 2);
}

void Blinky::CalculateTarget(Position mPac) {
    this->Target.ModPos(mPac.GetPos());
}

void Blinky::UpdatePos(unsigned char ActualBoard[], Pac& mPac, bool TimedStatus) {
    this->UpdateSpeed(mPac);
    this->UpdateStatus(mPac, TimedStatus);
    for (unsigned char i = 0; i < this->GetSpeed(); i++) {
        this->UpdateFacing(mPac);
        if (this->IsTargetToCalculate(mPac))
            this->CalculateTarget(mPac);
        this->CalculateDirection(ActualBoard);
        this->Move(this->GetDirection());
        this->CheckWrap();
    }
}
