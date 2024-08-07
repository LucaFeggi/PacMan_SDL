#include "Entity.hpp"

Entity::Entity(EntityType MyIdentity) {
    Identity = MyIdentity;
    Speed = 2;
    Direction = 0;
    Facing = 0;
    LifeStatement = true;
}

unsigned char Entity::GetIdentity() {
    return Identity;
}

unsigned char Entity::GetSpeed() {
    return Speed;
}

unsigned char Entity::GetDirection() {
    return Direction;
}

unsigned char Entity::GetFacing() {
    return Facing;
}

bool Entity::IsAlive() {
    return LifeStatement;
}

void Entity::ModSpeed(unsigned char NewSpeed) {
    Speed = NewSpeed;
}

void Entity::ModDirection(unsigned char NewDirection) {
    Direction = NewDirection;
}

void Entity::ModFacing(unsigned char NewFacing) {
    Facing = NewFacing;
}

void Entity::ModLifeStatement(bool NewLifeStatement) {
    LifeStatement = NewLifeStatement;
}

void Entity::GetPossiblePosition(short& x, short& y, Position::Direction mover) {
    switch (mover) {
        case Right:
            x++;
            break;
        case Up:
            y--;
            break;
        case Left:
            x--;
            break;
        case Down:
            y++;
            break;
        default:
            break;
    }
}

void Entity::CharBoardPos(unsigned char SideDir, Position& BoardPos, float cell_x, float cell_y) {
    switch (SideDir) {
        case 0:
            BoardPos.ModX(static_cast<short>(floor(cell_x)));
            BoardPos.ModY(static_cast<short>(floor(cell_y)));
            break;
        case 1:
            BoardPos.ModX(static_cast<short>(ceil(cell_x)));
            BoardPos.ModY(static_cast<short>(floor(cell_y)));
            break;
        case 2:
            BoardPos.ModX(static_cast<short>(floor(cell_x)));
            BoardPos.ModY(static_cast<short>(ceil(cell_y)));
            break;
        case 3:
            BoardPos.ModX(static_cast<short>(ceil(cell_x)));
            BoardPos.ModY(static_cast<short>(ceil(cell_y)));
            break;
        default:
            break;
    }
}

bool Entity::WallCollision(short x, short y, unsigned char ActualMap[], bool CanUseDoor) {
    float cell_x = x / static_cast<float>(BlockSize24);
    float cell_y = y / static_cast<float>(BlockSize24);
    Position BoardPos;
    for (unsigned char SideDir = 0; SideDir < 4; SideDir++) {
        this->CharBoardPos(SideDir, BoardPos, cell_x, cell_y);
        if (BlockType::Wall == ActualMap[BoardWidth * BoardPos.GetY() + abs(BoardPos.GetX() % BoardWidth)]) {
            return true;
        } else if (BlockType::Door == ActualMap[BoardWidth * BoardPos.GetY() + abs(BoardPos.GetX() % BoardWidth)]) {
            if (CanUseDoor)
                return false;
            else
                return true;
        }
    }
    return false;
}

void Entity::Move(unsigned char mover) {
    switch (mover) {
        case Right:
            this->ModX(this->GetX() + 1);
            break;
        case Up:
            this->ModY(this->GetY() - 1);
            break;
        case Left:
            this->ModX(this->GetX() - 1);
            break;
        case Down:
            this->ModY(this->GetY() + 1);
            break;
        default:
            break;
    }
}

void Entity::CheckWrap() {
    if (this->GetX() > WindowWidth + BlockSize24)
        this->ModX(-BlockSize24);
    if (this->GetX() < -BlockSize24)
        this->ModX(WindowWidth + BlockSize24);
}

bool Entity::IsColliding(Position other) {
    if (other.GetX() > this->GetX() - BlockSize24 && other.GetX() < this->GetX() + BlockSize24) {
        if (other.GetY() > this->GetY() - BlockSize24 && other.GetY() < this->GetY() + BlockSize24)
            return true;
    }
    return false;
}
