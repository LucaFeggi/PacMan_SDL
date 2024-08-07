#pragma once

class Position {
  public:
    enum Direction { Right, Up, Left, Down, Nowhere };

  public:
    Position(short x = 0, short y = 0);
    short GetX();
    short GetY();
    Position GetPos();
    void ModX(short NewX);
    void ModY(short NewY);
    void ModCoords(short NewX, short NewY);
    void ModPos(Position NewPos);
    bool operator==(Position other) { // see, i'm an expert...?
        return this->x == other.GetX() && this->y == other.GetY();
    }

  private:
    short x, y;
};
