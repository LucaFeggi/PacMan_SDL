class Game{
	public:
		Game();
		~Game();
		void ResetGhostsLifeStatement();
		void Start();
		void ModStartStatement(bool NewStartStatement);
		void Clock();
		void UpdatePositions(std::vector<unsigned char> &mover, bool TimedStatus);
		void Food();
		void EntityCollisions();
		void Update(std::vector<unsigned char> &mover);
		unsigned short GetLevel();
		void IncreaseLevel();
		void UpdateDifficulty();
		bool IsLevelCompleted();
		void ClearMover(std::vector<unsigned char> &mover);
	    void DeadlyPacGhostColl();
		void DeadlyGhostPacColl(Ghost &mGhost);
		void ModToWaka(bool NewWaka);
		void DeathSound();
		void ModDeathSoundStatement(bool NewDeathSoundStatement);
		void DrawLittleScore();
		bool Process(Timer &GameTimer, std::vector<unsigned char> &mover, unsigned short &StartTicks);
		void Draw();
		Sound mSound;
	private:
		Board mBoard;
		Pac mPac;
		Blinky mBlinky;
		Inky mInky;
		Pinky mPinky;
		Clyde mClyde;
		Ghost *mGhosts[4];
		std::vector<Entity*> mDrawables;
		Fruit mFruit;
		Timer MapAnimationTimer;
		LTexture Ready;
		LTexture GameOverTexture;
		unsigned char ActualMap[BoardHeight * BoardWidth];
		bool IsGameStarted;
		Timer GhostTimer;
		unsigned short ScatterTime;
		unsigned short ChasingTime;
		unsigned short GhostTimerTarget;
		bool TimedStatus;
		unsigned short Scorer;
		std::vector<Timer> LittleScoreTimer;
		std::vector<Position> LittleScorePositions;
		std::vector<unsigned short> LittleScoreScorers;
		unsigned short LittleTimerTarget;
		unsigned short Level;
		bool IsToScatterSound;
		bool IsToWakaSound;
		Timer WakaTimer;
		bool IsToDeathPacSound;
		unsigned char DeadGhostsCounter;
};

Game::Game() :
	mInky(&mBlinky, GhostTimer, mPac),
	mBlinky(GhostTimer, mPac),
	mPinky(GhostTimer, mPac),
	mClyde(GhostTimer, mPac) {
	Ready.loadFromRenderedText("ready!", Yellow);
	GameOverTexture.loadFromRenderedText("game  over", Red);
	mBoard.CopyBoard(ActualMap);
	IsGameStarted = false;
	ScatterTime = 7000;
	ChasingTime = 20000;
	GhostTimerTarget = ChasingTime;
	TimedStatus = false;
	Scorer = 200;
	LittleTimerTarget = 1000;
	Level = 1;
	IsToScatterSound = true;
	IsToWakaSound = true;
	IsToDeathPacSound = true;
	DeadGhostsCounter = 0;
	mGhosts[0] = &mBlinky;
	mGhosts[1] = &mInky;
	mGhosts[2] = &mPinky;
	mGhosts[3] = &mClyde;
	for (auto ghost : mGhosts) {
		ghost->SetScatterTime(ScatterTime);
	}
	mDrawables.push_back(&mPac);
	mDrawables.push_back(&mInky);
	mDrawables.push_back(&mBlinky);
	mDrawables.push_back(&mPinky);
	mDrawables.push_back(&mClyde);
}

Game::~Game(){
	Ready.free();
	GameOverTexture.free();
}

void Game::ResetGhostsLifeStatement(){
	for (auto ghost : mGhosts) {
		ghost->ModLifeStatement(true);
	}
}

void Game::Start(){
	if(!IsGameStarted){
		if(this->IsLevelCompleted()){
			mBoard.CopyBoard(ActualMap);
		}
		mBoard.ResetPosition(mPac);
		mBoard.ResetPosition(mBlinky);
		mBoard.ResetPosition(mInky);
		mBoard.ResetPosition(mPinky);
		mBoard.ResetPosition(mClyde);
		mPac.ChangeEnergyStatus(false);
		this->ResetGhostsLifeStatement();
		mPac.ResetCurrentLivingFrame();
		GhostTimer.Restart();
		IsGameStarted = true;
		GhostTimer.Start();
	}
	Ready.render(11 * BlockSize24, 20 * BlockSize24 - 5);
}

void Game::ModStartStatement(bool NewStartStatement){
	IsGameStarted = NewStartStatement;
}

void Game::Clock(){
	if(GhostTimer.GetTicks() > GhostTimerTarget){
		if(GhostTimerTarget == ScatterTime){
			if(mPac.IsEnergized()){
				mPac.ChangeEnergyStatus(false);
			}
			TimedStatus = false;
			GhostTimerTarget = ChasingTime;
			GhostTimer.Restart();
		}
		else if(GhostTimerTarget == ChasingTime){
			TimedStatus = true;
			GhostTimerTarget = ScatterTime;
			GhostTimer.Restart();
		}
	}
}

void Game::UpdatePositions(std::vector <unsigned char> &mover, bool TimedStatus){
	for (auto i = 0; i < 4; ++i) {
		mGhosts[i]->UpdatePosition(ActualMap, mPac, TimedStatus);
	}
	mPac.UpdatePos(mover, ActualMap);
}

void Game::Food(){
	switch(mPac.FoodCollision(ActualMap)){
		case 0:
			mBoard.ScoreIncrease(0);
			mFruit.UpdateFoodCounter();
			if(IsToWakaSound){
				mSound.PlayWaka();
				IsToWakaSound = false;
			}
			WakaTimer.Reset();
			break;
		case 1:
			mBoard.ScoreIncrease(1);
			mFruit.UpdateFoodCounter();
			mPac.ChangeEnergyStatus(true);
			Scorer = 200;
			GhostTimerTarget = ScatterTime;
			GhostTimer.Restart();
			if(IsToWakaSound){
				mSound.PlayWaka();
				IsToWakaSound = false;
			}
			WakaTimer.Reset();
			break;
		default:
			if(!WakaTimer.isStarted())
				WakaTimer.Start();
			break;
	}
	if(WakaTimer.GetTicks() > 300){
		mSound.StopWaka();
		IsToWakaSound = true;
	}
}

void Game::EntityCollisions(){
	if(!mPac.IsEnergized()){
		this->DeadlyPacGhostColl();
		if(!IsToScatterSound){
			DeadGhostsCounter = 0;
			mSound.StopScatterGhost();
			IsToScatterSound = true;
		}
	}
	else{
		if(IsToScatterSound){
			mSound.PlayScatterGhost();
			IsToScatterSound = false;
		}
		this->DeadlyGhostPacColl(mBlinky);
		this->DeadlyGhostPacColl(mInky);
		this->DeadlyGhostPacColl(mPinky);
		this->DeadlyGhostPacColl(mClyde);
		if(DeadGhostsCounter == 4){
			if(!IsToScatterSound){
				mSound.StopScatterGhost();
			}
		}
	}
	if(mFruit.IsEatable()){
		if(mPac.IsColliding(mFruit)){
			mFruit.StartScoreTimer();
			mBoard.ScoreIncrease(mFruit.GetScoreValue());
			mFruit.Despawn();
			mSound.PlayEatFruit();
		}
		else{
			if(mFruit.CheckDespawn())
				mFruit.Despawn();
		}
	}
}

void Game::Update(std::vector <unsigned char> &mover){
	this->Clock();
	this->UpdatePositions(mover, TimedStatus);
	this->Food();
	if(mBoard.IsExtraLife())
		mSound.PlayExtraLife();
	this->EntityCollisions();
}

unsigned short Game::GetLevel(){
	return Level;
}

void Game::IncreaseLevel(){
	Level++;
}

void Game::UpdateDifficulty(){
	if(Level % 3 == 0){
		ChasingTime += 1000;
		if(ScatterTime > 2000){
			ScatterTime -= 1000;
		}
	}
}

bool Game::IsLevelCompleted(){
	for(unsigned short i = 0; i < BoardHeight * BoardWidth; i++){
		if(ActualMap[i] == BlockType::Pellet)
			return false;
		if(ActualMap[i] == BlockType::Energizer)
			return false;
	}
	return true;
}

void Game::ClearMover(std::vector<unsigned char> &mover){
	while(!mover.empty())
		mover.erase(mover.begin());
	mover.push_back(0);
}

void Game::DeadlyPacGhostColl(){
	if(
	   (mPac.IsColliding(mBlinky.GetPos()) && mBlinky.IsAlive()) ||
	   (mPac.IsColliding(mInky.GetPos()) && mInky.IsAlive()) 	||
	   (mPac.IsColliding(mPinky.GetPos()) && mPinky.IsAlive())   ||
	   (mPac.IsColliding(mClyde.GetPos()) && mClyde.IsAlive())
	)
	mPac.ModLifeStatement(false);
}

void Game::DeadlyGhostPacColl(Ghost &mGhost){
	if(mPac.IsColliding(mGhost.GetPos()) && mGhost.IsAlive()){
		mGhost.ModLifeStatement(false);
		mBoard.ScoreIncrease(Scorer);
		LittleScoreScorers.push_back(Scorer);
		Timer mGhostLilTimer;
		mGhostLilTimer.Start();
		LittleScoreTimer.push_back(mGhostLilTimer);
		Position ThisLilPos;
		ThisLilPos.ModPos(mGhost.GetPos());
		LittleScorePositions.push_back(ThisLilPos);
		Scorer *= 2;
		mSound.PlayGhostDeath();
		DeadGhostsCounter++;
	}
}

void Game::ModToWaka(bool NewWaka){
	IsToWakaSound = NewWaka;
}

void Game::DeathSound(){
	if(IsToDeathPacSound){
		mSound.StopWaka();
		mSound.PlayPacDeath();
		IsToDeathPacSound = false;
	}
}

void Game::ModDeathSoundStatement(bool NewDeathSoundStatement){
	IsToDeathPacSound = NewDeathSoundStatement;
}

void Game::DrawLittleScore(){
	for(unsigned char i = 0; i < LittleScoreTimer.size(); i++){
		Timer ThisLilTimer = LittleScoreTimer.at(i);
		if(ThisLilTimer.GetTicks() < LittleTimerTarget){
			LTexture ThisLilTexture;
			std::stringstream ss;
			ss << LittleScoreScorers.at(i);
			ThisLilTexture.loadFromRenderedText(ss.str(), White, 1);
			Position ThisLilPos = LittleScorePositions.at(i);
			ThisLilTexture.render(ThisLilPos.GetX(), ThisLilPos.GetY() - BlockSize24/2 );
			ThisLilTexture.free();
		}
		else{
			LittleScoreScorers.erase(LittleScoreScorers.begin() + i);
			LittleScoreTimer.erase(LittleScoreTimer.begin() + i);
			LittleScorePositions.erase(LittleScorePositions.begin() + i);
		}
	}
}

bool Game::Process(Timer &GameTimer, std::vector<unsigned char> &mover, unsigned short &StartTicks){
	//Returns false when should render the last animation frame.
	//It's bad looking, so I don't want to render it.
	if(GameTimer.GetTicks() < StartTicks){
			this->Start();
		}
		else{
			if(mPac.IsAlive()){
				if(!this->IsLevelCompleted()){
					this->Update(mover);
				}
				else{
					if(!MapAnimationTimer.isStarted()){
						if(StartTicks != 2500)
							StartTicks = 2500;
						mPac.ResetCurrentLivingFrame();
						mFruit.Despawn();
						mFruit.ResetFoodCounter();
						mSound.StopWaka();
						mSound.StopScatterGhost();
						this->ModToWaka(true);
						MapAnimationTimer.Start();
					}
					else if(MapAnimationTimer.GetTicks() > 2100){
						this->ClearMover(mover);
						this->IncreaseLevel();
						mFruit.ModCurrentFruit(this->GetLevel());
						UpdateDifficulty();
						this->ModStartStatement(false);
						MapAnimationTimer.Reset();
						GameTimer.Start();
						return false;
					}
				}
			}
			else{
				if(mBoard.GetLives() > 0){
					if(mPac.IsDeadAnimationEnded()){
						if(StartTicks != 2500)
							StartTicks = 2500;
						this->ClearMover(mover);
						mPac.ModDeadAnimationStatement(false);
						mPac.ModLifeStatement(true);
						mBoard.DecreaseLives();
						mFruit.Despawn();
						this->ModToWaka(true);
						this->ModDeathSoundStatement(true);
						this->ModStartStatement(false);
						GameTimer.Restart();
						return false;
					}
				}
				else{
					if(mPac.IsDeadAnimationEnded()){
						this->ModStartStatement(false);
					}
				}
				this->DeathSound();
			}
		}
	return true;
}

void Game::Draw(){
	mBoard.SetHighScore();
	mBoard.SetScore();
	mBoard.Draw(ActualMap, MapAnimationTimer);
	if(!IsGameStarted){
		GameOverTexture.render(9 * BlockSize24, 20 * BlockSize24 - 5);
		return;
	}
	mFruit.Draw();
	if(!MapAnimationTimer.isStarted()){
		this->DrawLittleScore();
	}

	for (auto drawable : mDrawables) {
		drawable->Draw();
	}
}