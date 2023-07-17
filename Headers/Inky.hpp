class Inky : public Ghost{
	private:
		Blinky *mBlinky;
	public:
		Inky(Blinky *mBLinky, Timer &timer, Pac &pacman);
		void CalculateTarget(Pac &mPac);
};
	
Inky::Inky(Blinky *mBlinky, Timer &timer, Pac &pacman) : Ghost(Cyan, EntityType::eInky, timer, pacman){
	this->mBlinky = mBlinky;
	this->ScatterTarget.ModCoords(26 * BlockSize24 + BlockSize24 / 2, 35 * BlockSize24 + BlockSize24 / 2);
	this->Home.ModCoords(11 * BlockSize24 + BlockSize24 / 2, 17 * BlockSize24 + BlockSize24 / 2);
	this->ModFacing(1);
}

void Inky::CalculateTarget(Pac &mPac) {
	short x = mPac.GetPos().GetX();
	short y = mPac.GetPos().GetY();
	switch(mPac.GetDirection()){
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
	short x1 = x - mBlinky->GetPos().GetX();
	short y1 = y - mBlinky->GetPos().GetY();
	this->Target.ModCoords(x + x1, y + y1);
}