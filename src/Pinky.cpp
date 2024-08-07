#include "Pinky.hpp"

Pinky::Pinky() : Ghost(Pink, EntityType::ePinky) {
    this->ScatterTarget.ModCoords(2 * BlockSize24 + BlockSize24 / 2, BlockSize24 / 2);
    this->Home.ModCoords(13 * BlockSize24 + BlockSize24 / 2, 17 * BlockSize24 + BlockSize24 / 2);
}

void Pinky::CalculateTarget(Entity mPac) {
    short x = mPac.GetX();
    short y = mPac.GetY();
    switch (mPac.GetDirection()) {
        case Right:
            x += 4 * BlockSize24;
            break;
        case Up:
            y -= 4 * BlockSize24;
            break;
        case Left:
            x -= 4 * BlockSize24;
            break;
        case Down:
            y += 4 * BlockSize24;
            break;
        default:
            break;
    }
    this->Target.ModCoords(x, y);
}

void Pinky::UpdatePos(unsigned char ActualBoard[], Pac& mPac, bool TimedStatus) {
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
