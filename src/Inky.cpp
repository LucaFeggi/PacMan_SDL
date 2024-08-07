#include "Inky.hpp"

Inky::Inky() : Ghost(Cyan, EntityType::eInky) {
    this->ScatterTarget.ModCoords(26 * BlockSize24 + BlockSize24 / 2, 35 * BlockSize24 + BlockSize24 / 2);
    this->Home.ModCoords(11 * BlockSize24 + BlockSize24 / 2, 17 * BlockSize24 + BlockSize24 / 2);
}

void Inky::CalculateTarget(Entity mPac, Position mBlinky) {
    short x = mPac.GetX();
    short y = mPac.GetY();
    switch (mPac.GetDirection()) {
        case Right:
            x += 2 * BlockSize24;
            break;
        case Up:
            y -= 2 * BlockSize24;
            break;
        case Left:
            x -= 2 * BlockSize24;
            break;
        case Down:
            y += 2 * BlockSize24;
            break;
        default:
            break;
    }
    short x1 = x - mBlinky.GetX();
    short y1 = y - mBlinky.GetY();
    this->Target.ModCoords(x + x1, y + y1);
}

void Inky::UpdatePos(unsigned char ActualBoard[], Pac& mPac, Position mBlinky, bool TimedStatus) {
    this->UpdateSpeed(mPac);
    this->UpdateStatus(mPac, TimedStatus);
    for (unsigned char i = 0; i < this->GetSpeed(); i++) {
        this->UpdateFacing(mPac);
        if (this->IsTargetToCalculate(mPac))
            this->CalculateTarget(mPac, mBlinky);
        this->CalculateDirection(ActualBoard);
        this->Move(this->GetDirection());
        this->CheckWrap();
    }
}
