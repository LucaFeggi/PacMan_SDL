class Fruit : public Position{
	public:
		Fruit();
		~Fruit();
		void ModCurrentFruit(unsigned short ActualActualLevel);
		void UpdateFoodCounter();
		bool IsEatable();
		unsigned short GetScoreValue();
		void StartScoreTimer();
		void ResetScoreTimer();
		bool CheckDespawn();
		void Despawn();
		void ResetFoodCounter();
		void Draw();
	private:
		LTexture FruitTexture;
		Timer FruitTimer;
		Timer ScoreTimer;
		SDL_Rect FruitSpriteClips[FruitFrames];
		unsigned char CurrentFruit;
		unsigned short FruitDuration;
		unsigned char FoodCounter;
};

Fruit::Fruit(){
	FruitTexture.loadFromFile("Textures/Fruit32.png");
	InitFrames(FruitFrames, FruitSpriteClips);
	this->ModCoords(13 * BlockSize24 + BlockSize24 / 2, 20 * BlockSize24);
	CurrentFruit = 0;
	FruitDuration = 9000;
	FoodCounter = 0;
}

Fruit::~Fruit(){
	FruitTexture.free();
}

void Fruit::ModCurrentFruit(unsigned short ActualLevel){
	if(ActualLevel > 21){
		if(CurrentFruit != 7)
			CurrentFruit = 7;
	}
	else{
		CurrentFruit = static_cast<unsigned char>(floor((ActualLevel - 1) / 3.0f));
	}
}

void Fruit::UpdateFoodCounter(){
	FoodCounter++;
	if(FoodCounter == 70 || FoodCounter == 200)
		if(!FruitTimer.isStarted())
			FruitTimer.Start();
}

bool Fruit::IsEatable(){
	if(FruitTimer.isStarted())
		return true;
	return false;
}

unsigned short Fruit::GetScoreValue(){
	return ScoreTable[CurrentFruit];
}

void Fruit::StartScoreTimer(){
	ScoreTimer.Start();
}

void Fruit::ResetScoreTimer(){
	if(ScoreTimer.GetTicks() > 1000)
		ScoreTimer.Reset();
}

bool Fruit::CheckDespawn(){
	if(FruitTimer.GetTicks() > FruitDuration)
		return true;
	return false;
}

void Fruit::Despawn(){
	FruitTimer.Reset();
}

void Fruit::ResetFoodCounter(){
	FoodCounter = 0;
}

void Fruit::Draw(){
	if(FruitTimer.isStarted()){
		CurrentClip = &FruitSpriteClips[CurrentFruit];
		FruitTexture.render((this->GetX()-4)*scale, (this->GetY()- 4)*scale, 0, CurrentClip);	
	}

	if(ScoreTimer.isStarted() && ScoreTimer.GetTicks() < 1000){
		std::stringstream ss;
		ss << ScoreTable[CurrentFruit];
		LTexture ScoreTexture;
		ScoreTexture.loadFromRenderedText(ss.str(), White, 1);
		ScoreTexture.render((this->GetX())*scale, (this->GetY() - BlockSize24 / 2)*scale);
		ScoreTexture.free();
	}
}
