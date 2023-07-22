class Clyde : public Ghost{
	public:
		Clyde(Timer &timer, Pac &pacman);
		void CalculateTarget(Pac &mPac);
};

Clyde::Clyde(Timer &timer, Pac &pacman) : Ghost(Orange, EntityType::eClyde, timer, pacman){
	this->ScatterTarget.ModCoords(BlockSize24 / 2, 35 * BlockSize24 + BlockSize24/ 2);
	this->Home.ModCoords(15 * BlockSize24 + BlockSize24 / 2, 17 * BlockSize24 + BlockSize24 / 2);
	this->ModFacing(1);
}

void Clyde::CalculateTarget(Pac &mPac) {
	float DistX = abs(this->GetPos().GetX() - mPac.GetPos().GetX());
	if(DistX > WindowWidth / 2)
		DistX = WindowWidth - DistX;
	float Dist = static_cast<float>(sqrt(pow(DistX, 2) + pow(this->GetPos().GetY() - mPac.GetPos().GetY(), 2)));
	if(Dist > 8 * BlockSize24)
		this->Target.ModPos(mPac.GetPos());
	else
		this->Target.ModPos(this->ScatterTarget.GetPos());
}