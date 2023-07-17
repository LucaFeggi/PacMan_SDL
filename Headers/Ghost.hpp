class Ghost : public Entity{
	public:
		Ghost(SDL_Color MyColor, EntityType MyIdentity, Timer &MyTimer, Pac &Pacman);
		~Ghost();
		bool IsTargetToCalculate(Pac &mPac);
		void PossDirsBubbleSort(std::vector<float> &Distances, std::vector<unsigned char> &PossibleDirections);
		void CalculateDirection(unsigned char ActualMap[]);
		bool IsHome();
		void ModStatus(bool NewStatus);
		void UpdateStatus(Pac &mPac, bool TimedStatus);
		void UpdateFacing(Pac &mPac);
		void UpdateSpeed(Pac &mPac);
		void UpdatePosition(unsigned char board[], Pac &mPac, bool TimedStatus);
		virtual void CalculateTarget(Pac &mPac) = 0;
		void Draw();
		void SetScatterTime(unsigned short value) { ScatterTime = value; }
		Position Target;
		Position ScatterTarget;
		Position DoorTarget;
		Position Home;
	private:
		LTexture Body;
		LTexture Eyes;
		SDL_Rect GhostBodySpriteClips[GhostBodyFrames];
		SDL_Rect GhostEyeSpriteClips[GhostEyeFrames];
		SDL_Color Color;
		unsigned char CurrentBodyFrame;
		unsigned short ScatterTime;
		bool CanUseDoor;
		bool Status; // false -> chase	true -> scatter
		Timer MyTimer;
		Pac &pacman;
};

Ghost::Ghost(SDL_Color MyColor, EntityType MyIdentity, Timer &MyTimer, Pac &Pacman) : Entity(MyIdentity), pacman(Pacman){
	Body.loadFromFile("Textures/GhostBody32.png");
	Eyes.loadFromFile("Textures/GhostEyes32.png");
	InitFrames(GhostBodyFrames, GhostBodySpriteClips);
	InitFrames(GhostEyeFrames, GhostEyeSpriteClips);
	Color = MyColor;
	CurrentBodyFrame = 0;
	CanUseDoor = false;
	Status = false;
	DoorTarget.ModCoords(13 * BlockSize24 + BlockSize24 / 2, 15 * BlockSize24);
	this->MyTimer = MyTimer;
}

Ghost::~Ghost(){
	Body.free();
	Eyes.free();
}

bool Ghost::IsTargetToCalculate(Pac &mPac){

	if(!this->IsAlive()){
		CanUseDoor = true;
		Target.ModPos(Home);
		if(this->GetPos() == Home.GetPos())
			this->ModLifeStatement(true);
		return false;
	}
	
	if(this->IsHome() && mPac.IsEnergized()){
		if(this->GetPos() == Home.GetPos())
			Target.ModY(this->Home.GetY() - BlockSize24);
		else if(this->GetPos().GetX() == Home.GetX() && this->GetPos().GetY() == Home.GetY() - BlockSize24)
			Target.ModY(this->Home.GetY());		
		return false;
	}

	if(this->IsHome() && this->IsAlive()){
		CanUseDoor = true;
		Target.ModPos(this->DoorTarget);
		return false;
	}

	CanUseDoor = false;
	switch(Status){
		case false:
			return true;
		case true:
			Target.ModPos(this->ScatterTarget);
			return false;
	}
	
}

void Ghost::PossDirsBubbleSort(std::vector<float> &Distances, std::vector<unsigned char> &PossibleDirections){
	for(unsigned char i = 0; i < Distances.size(); i++){
		for(unsigned char j = 0; j < Distances.size(); j++){
			if(Distances.at(i) < Distances.at(j)){
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

void Ghost::CalculateDirection(unsigned char ActualMap[]){
	std::vector<float> Distances;
	std::vector<unsigned char> PossibleDirections;
	for(unsigned char i = 0; i < 4; i++){
		short x = this->GetPos().GetX();
		short y = this->GetPos().GetY();
		this->GetPossiblePosition(x, y, i);
		if(!this->WallCollision(x, y, ActualMap, CanUseDoor)){
			float DistX = abs(x - this->Target.GetX());
			if(DistX > WindowWidth / 2)
				DistX = WindowWidth - DistX;
			float Dist = static_cast<float>(sqrt(pow(DistX, 2) + pow(y - Target.GetY(), 2)));
			Distances.push_back(Dist);
			PossibleDirections.push_back(i);
		}
	}

	if(PossibleDirections.size() == 1){
		this->ModDirection(PossibleDirections.at(0));
		return;
	}
	
	this->PossDirsBubbleSort(Distances, PossibleDirections);
	
	for(unsigned char i = 0; i < PossibleDirections.size(); i++){
		if(PossibleDirections.at(i) != (this->GetDirection() + 2) % 4){
			this->ModDirection(PossibleDirections.at(i));
			return;
		}
	}
}

bool Ghost::IsHome(){
	if(this->GetPos().GetX() > 11 * BlockSize24 && this->GetPos().GetX() < 17 * BlockSize24){
		if(this->GetPos().GetY() > 15 * BlockSize24 && this->GetPos().GetY() < 18 * BlockSize24)
			return true;
	}
	return false;
}

void Ghost::ModStatus(bool NewStatus){
	Status = NewStatus;
}

void Ghost::UpdateStatus(Pac &mPac, bool TimedStatus){

	if(mPac.IsEnergized()){
		if(!Status)
			Status = true;
		return;
	}
	
	switch(TimedStatus){
		case false:
			if(Status)
				Status = false;
			return;
		case true:
			if(!Status)
				Status = true;
			return;
	}
	
}

void Ghost::UpdateFacing(Pac &mPac){
	
	if(this->IsHome()){
		if(this->GetDirection() == 3)
			this->ModFacing(3);
		else
			this->ModFacing(1);
		return;
	}
	
	if(mPac.IsEnergized()){
		if(!this->IsAlive())
			this->ModFacing(this->GetDirection());
		else
			this->ModFacing(4);
		return;
	}
	
	this->ModFacing(this->GetDirection());
	
}

void Ghost::UpdateSpeed(Pac &mPac){
	
	if(!this->IsAlive() && this->GetSpeed() != 6){
		this->ModSpeed(6);
		return;
	}
	
	if(mPac.IsEnergized()){
		if(this->GetSpeed() != 1)
			this->ModSpeed(1);
	}
	else{
		if(this->GetSpeed() != 2)
			this->ModSpeed(2);
	}
	
}

void Ghost::UpdatePosition(unsigned char board[], Pac &mPac, bool TimedStatus) {
	this->UpdateSpeed(mPac);
	this->UpdateStatus(mPac, TimedStatus);
	for(unsigned char i = 0; i < this->GetSpeed(); i++){
		this->UpdateFacing(mPac);
		if(this->IsTargetToCalculate(mPac))
			this->CalculateTarget(mPac);
		this->CalculateDirection(board);
		this->Move(this->GetDirection());
		this->CheckWrap();
	}
}

void Ghost::Draw() {
	if(pacman.IsEnergized() && this->IsAlive() && !this->IsHome()){
		Body.setColor(0, 0, 255);
		if(MyTimer.GetTicks() > ScatterTime - 2000){
			if((MyTimer.GetTicks() / 250) % 2 == 1){
				Body.setColor(255, 255, 255);
				Eyes.setColor(255, 0, 0);
			}
			else{
				Eyes.setColor(255, 255, 255);
			}
		}
		else{
			Eyes.setColor(255, 255, 255);
		}
	}
	else{
		Eyes.setColor(255, 255, 255);
		Body.setColor(Color.r, Color.g, Color.b);
	}
		
	if(this->IsAlive()){
		CurrentClip = &GhostBodySpriteClips[CurrentBodyFrame / GhostBodyFrames];
		Body.render(this->GetPos().GetX() - 4, this->GetPos().GetY() - 4, 0, CurrentClip);
	}
	CurrentClip = &GhostEyeSpriteClips[this->GetFacing()];
	Eyes.render(this->GetPos().GetX() - 4, this->GetPos().GetY() - 4, 0, CurrentClip);
	CurrentBodyFrame++;
	if(CurrentBodyFrame / GhostBodyFrames >= GhostBodyFrames){
		CurrentBodyFrame = 0;
	}
}