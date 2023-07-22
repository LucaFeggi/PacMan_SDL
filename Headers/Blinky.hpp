class Blinky : public Ghost{
	private:
		void CalculateTarget(Pac &mPac);
	public:
		Blinky(Timer &timer, Pac &pacman);
};

Blinky::Blinky(Timer &timer, Pac &pacman) : Ghost(Red, EntityType::eBlinky, timer, pacman){
	this->ScatterTarget.ModCoords(25 * BlockSize24 + BlockSize24 / 2, BlockSize24 / 2);
	this->Home.ModCoords(13 * BlockSize24 + BlockSize24 / 2, 17 * BlockSize24 + BlockSize24 / 2);
	this->ModFacing(0);
}

void Blinky::CalculateTarget(Pac &mPac) {
	this->Target.ModPos(mPac.GetPos());
}