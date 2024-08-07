#include "Ghost.hpp"

Ghost::Ghost(SDL_Color MyColor, EntityType MyIdentity) : Entity(MyIdentity) {
    Body.loadFromFile("Textures/GhostBody32.png");
    Eyes.loadFromFile("Textures/GhostEyes32.png");
    InitFrames(GhostBodyFrames, GhostBodySpriteClips);
    InitFrames(GhostEyeFrames, GhostEyeSpriteClips);
    Color = MyColor;
    CurrentBodyFrame = 0;
    CanUseDoor = false;
    Status = false;
    DoorTarget.ModCoords(13 * BlockSize24 + BlockSize24 / 2, 15 * BlockSize24);
}

Ghost::~Ghost() {
    Body.free();
    Eyes.free();
}

bool Ghost::IsTargetToCalculate(Pac& mPac) {
    if (!this->IsAlive()) {
        CanUseDoor = true;
        Target.ModPos(Home);
        if (this->GetPos() == Home.GetPos())
            this->ModLifeStatement(true);
        return false;
    }

    if (this->IsHome() && mPac.IsEnergized()) {
        if (this->GetPos() == Home.GetPos())
            Target.ModY(this->Home.GetY() - BlockSize24);
        else if (this->GetX() == Home.GetX() && this->GetY() == Home.GetY() - BlockSize24)
            Target.ModY(this->Home.GetY());
        return false;
    }

    if (this->IsHome() && this->IsAlive()) {
        CanUseDoor = true;
        Target.ModPos(this->DoorTarget);
        return false;
    }

    CanUseDoor = false;
    switch (Status) {
        case false:
            return true;
        case true:
            Target.ModPos(this->ScatterTarget);
            return false;
    }
}

void Ghost::PossDirsBubbleSort(std::vector<float>& Distances, std::vector<unsigned char>& PossibleDirections) {
    for (unsigned char i = 0; i < Distances.size(); i++) {
        for (unsigned char j = 0; j < Distances.size(); j++) {
            if (Distances.at(i) < Distances.at(j)) {
                float temp1 = Distances.at(i);
                Distances.at(i) = Distances.at(j);
                Distances.at(j) = temp1;
                unsigned char temp2 = PossibleDirections.at(i);
                PossibleDirections.at(i) = PossibleDirections.at(j);
                PossibleDirections.at(j) = temp2;
            }
        }
    }
}

void Ghost::CalculateDirection(unsigned char ActualMap[]) {
    std::vector<float> Distances;
    std::vector<unsigned char> PossibleDirections;
    for (unsigned char i = 0; i < 4; i++) {
        short x = this->GetX();
        short y = this->GetY();
        this->GetPossiblePosition(x, y, (Position::Direction)i);
        if (!this->WallCollision(x, y, ActualMap, CanUseDoor)) {
            float DistX = abs(x - this->Target.GetX());
            if (DistX > WindowWidth / 2)
                DistX = WindowWidth - DistX;
            float Dist = static_cast<float>(sqrt(pow(DistX, 2) + pow(y - Target.GetY(), 2)));
            Distances.push_back(Dist);
            PossibleDirections.push_back(i);
        }
    }

    if (PossibleDirections.size() == 1) {
        this->ModDirection(PossibleDirections.at(0));
        return;
    }

    this->PossDirsBubbleSort(Distances, PossibleDirections);

    for (unsigned char i = 0; i < PossibleDirections.size(); i++) {
        if (PossibleDirections.at(i) != (this->GetDirection() + 2) % 4) {
            this->ModDirection(PossibleDirections.at(i));
            return;
        }
    }
}

bool Ghost::IsHome() {
    if (this->GetX() > 11 * BlockSize24 && this->GetX() < 17 * BlockSize24) {
        if (this->GetY() > 15 * BlockSize24 && this->GetY() < 18 * BlockSize24)
            return true;
    }
    return false;
}

void Ghost::ModStatus(bool NewStatus) {
    Status = NewStatus;
}

void Ghost::UpdateStatus(Pac& mPac, bool TimedStatus) {
    if (mPac.IsEnergized()) {
        if (!Status)
            Status = true;
        return;
    }

    switch (TimedStatus) {
        case false:
            if (Status)
                Status = false;
            return;
        case true:
            if (!Status)
                Status = true;
            return;
    }
}

void Ghost::UpdateFacing(Pac& mPac) {
    if (this->IsHome()) {
        if (this->GetDirection() == 3)
            this->ModFacing(3);
        else
            this->ModFacing(1);
        return;
    }

    if (mPac.IsEnergized()) {
        if (!this->IsAlive())
            this->ModFacing(this->GetDirection());
        else
            this->ModFacing(4);
        return;
    }

    this->ModFacing(this->GetDirection());
}

void Ghost::UpdateSpeed(Pac& mPac) {
    if (!this->IsAlive() && this->GetSpeed() != 6) {
        this->ModSpeed(6);
        return;
    }

    if (mPac.IsEnergized()) {
        if (this->GetSpeed() != 1)
            this->ModSpeed(1);
    } else {
        if (this->GetSpeed() != 2)
            this->ModSpeed(2);
    }
}

void Ghost::Draw(Pac& mPac, Timer mGhostTimer, unsigned short mTimerTarget) {
    if (mPac.IsEnergized() && this->IsAlive() && !this->IsHome()) {
        Body.setColor(0, 0, 255);
        if (mGhostTimer.GetTicks() > mTimerTarget - 2000) {
            if ((mGhostTimer.GetTicks() / 250) % 2 == 1) {
                Body.setColor(255, 255, 255);
                Eyes.setColor(255, 0, 0);
            } else {
                Eyes.setColor(255, 255, 255);
            }
        } else {
            Eyes.setColor(255, 255, 255);
        }
    } else {
        Eyes.setColor(255, 255, 255);
        Body.setColor(Color.r, Color.g, Color.b);
    }

    if (this->IsAlive()) {
        CurrentClip = &GhostBodySpriteClips[CurrentBodyFrame / GhostBodyFrames];
        Body.render(this->GetX() - 4, this->GetY() - 4, 0, CurrentClip);
    }
    CurrentClip = &GhostEyeSpriteClips[this->GetFacing()];
    Eyes.render(this->GetX() - 4, this->GetY() - 4, 0, CurrentClip);
    CurrentBodyFrame++;
    if (CurrentBodyFrame / GhostBodyFrames >= GhostBodyFrames) {
        CurrentBodyFrame = 0;
    }
}
