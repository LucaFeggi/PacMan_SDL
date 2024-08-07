#include "Clyde.hpp"

Clyde::Clyde() : Ghost(Orange, EntityType::eClyde) {
    this->ScatterTarget.ModCoords(BlockSize24 / 2, 35 * BlockSize24 + BlockSize24 / 2);
    this->Home.ModCoords(15 * BlockSize24 + BlockSize24 / 2, 17 * BlockSize24 + BlockSize24 / 2);
}

void Clyde::CalculateTarget(Position mPac) {
    float DistX = abs(this->GetX() - mPac.GetX());
    if (DistX > WindowWidth / 2)
        DistX = WindowWidth - DistX;
    float Dist = static_cast<float>(sqrt(pow(DistX, 2) + pow(this->GetY() - mPac.GetY(), 2)));
    if (Dist > 8 * BlockSize24)
        this->Target.ModPos(mPac.GetPos());
    else
        this->Target.ModPos(this->ScatterTarget.GetPos());
}

void Clyde::UpdatePos(unsigned char ActualBoard[], Pac& mPac, bool TimedStatus) {
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
