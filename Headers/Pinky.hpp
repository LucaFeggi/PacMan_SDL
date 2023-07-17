class Pinky : public Ghost{
	public:
		Pinky(Timer &timer, Pac &pacman);
		void CalculateTarget(Pac &mPac);
};

Pinky::Pinky(Timer &timer, Pac &pacman) : Ghost(Pink, EntityType::ePinky, timer, pacman){
	this->ScatterTarget.ModCoords(2 * BlockSize24 + BlockSize24 / 2, BlockSize24 / 2);
	this->Home.ModCoords(13 * BlockSize24 + BlockSize24 / 2, 17 * BlockSize24 + BlockSize24 / 2);
	this->ModFacing(1);
}

void Pinky::CalculateTarget(Pac &mPac) {
	short x = mPac.GetPos().GetX();
	short y = mPac.GetPos().GetY();
	switch(mPac.GetDirection()){
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