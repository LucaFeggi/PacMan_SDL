class Position {

	private:
		short x, y;

	public:
		Position(short x = 0, short y = 0);

		short GetX();
		short GetY();
		Position GetPos();
		void ModX(short NewX);
		void ModY(short NewY);
		void ModCoords(short NewX, short NewY);
		void ModPos(Position NewPos);
		bool operator == (Position other){	//see, i'm an expert...?
			return this->x == other.GetX() && this->y == other.GetY();
		}
};

Position::Position(short x, short y) {
	this->x = x;
	this->y = y;
}

short Position::GetX() {
	return this->x;
}

short Position::GetY() {
	return this->y;
}

Position Position::GetPos() {
	Position MyPos(this->x, this->y);
	return MyPos;
}

void Position::ModX(short NewX) {
	this->x = NewX;
}

void Position::ModY(short NewY) {
	this->y = NewY;	
}

void Position::ModCoords(short NewX, short NewY) {
	this->x = NewX;
	this->y = NewY;
}

void Position::ModPos(Position NewPos) {
	this->x = NewPos.GetX();
	this->y = NewPos.GetY();
}
