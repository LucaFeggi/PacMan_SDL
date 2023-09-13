class Game {

	private:
        // PRIVATE ATRIBUTES
        
        // first first live screen wait time
	    unsigned short StartTicksInitial = 4500;


        // board
		Board mBoard;
        
        // characters
		Pac mPac;
		Blinky mBlinky;
		Inky mInky;
		Pinky mPinky;
		Clyde mClyde;
		Fruit mFruit;
        
        // timers
	    Timer GameTimer;
		Timer MapAnimationTimer;
		Timer GhostTimer;
        //  ghost chasing timer
		Timer WakaTimer;
        
        // texture
        LTexture Ready;
		LTexture GameOverTexture;
        

		bool IsGameStarted;
		bool TimedStatus;
		bool IsToDeathPacSound;
		bool IsToScatterSound;
		bool IsToWakaSound;

        
        // chasing ghost times
		unsigned short ScatterTime;
		unsigned short ChasingTime;
		unsigned short GhostTimerTarget;

		unsigned short Scorer;
		unsigned short LittleTimerTarget;
		unsigned short Level;
		unsigned char DeadGhostsCounter;

		std::vector<Timer> LittleScoreTimer;
		std::vector<Position> LittleScorePositions;
		std::vector<unsigned short> LittleScoreScorers;

		Sound mSound;


	public:
        
        // PUBLIC ATTRIBUTES

	    std::vector<unsigned char> mover;
        
        // PUBLIC METHODS 

        // constructor
        Game();
        ~Game();
        
        // start game
		void Start();

		void ResetGhostsLifeStatement();
		void ResetGhostsFacing();


		void ModStartStatement(bool NewStartStatement);

		void Clock();

		void UpdatePositions(std::vector<unsigned char> &mover, bool TimedStatus);
		void Food();
		void EntityCollisions();

		void Update();

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
        
        bool keyboardProcess();

        //  Returns false when
        //  should render the last animation frame.
        //  It's bad looking, so I don't want to render it.
		bool Process();
		void Draw();

};

Game::Game() {

    mover.push_back(Right);

    IsGameStarted = false;
    
    // ghost times

    // ghost away movement time
    ScatterTime = 7000;
    
    // ghost towards movement time
    ChasingTime = 20000;
    GhostTimerTarget = ChasingTime;



    TimedStatus = false;
    Scorer = 200;
    LittleTimerTarget = 1000;
    Level = 1;

    //  sound
    IsToScatterSound = true;
    IsToWakaSound = true;
    IsToDeathPacSound = true;

    DeadGhostsCounter = 0;

    mSound.PlayIntro();
    GameTimer.Start();
}

Game::~Game(){
    Ready.free();
    GameOverTexture.free();
}

void Game::ResetGhostsLifeStatement(){
	mBlinky.ModLifeStatement(true);
	mInky.ModLifeStatement(true);
	mPinky.ModLifeStatement(true);
	mClyde.ModLifeStatement(true);
}

void Game::ResetGhostsFacing(){
	mBlinky.ModFacing(0);
	mInky.ModFacing(1);
	mPinky.ModFacing(1);
	mClyde.ModFacing(1);
}

// new game
void Game::Start() {
    // game not started
	if(!IsGameStarted) {
        // level completed
		if(this->IsLevelCompleted()){
            // numericboard, starting board, is copied into ActualMap
			mBoard.CopyBoard();
		}
        
        //  starting positions
		mBoard.ResetPosition(mPac);
		mBoard.ResetPosition(mBlinky);
		mBoard.ResetPosition(mInky);
		mBoard.ResetPosition(mPinky);
		mBoard.ResetPosition(mClyde);

		mPac.ChangeEnergyStatus(false);

		this->ResetGhostsLifeStatement();
		this->ResetGhostsFacing();

		mPac.ResetCurrentLivingFrame();
	    
        // ghost timer
        GhostTimer.Restart();
		IsGameStarted = true;
		GhostTimer.Start();
	}

	Ready.loadFromRenderedText("ready!", Yellow);
	Ready.render(11 * BlockSize24, 20 * BlockSize24 - 5);
}

void Game::ModStartStatement(bool NewStartStatement){
	IsGameStarted = NewStartStatement;
}

void Game::Clock(){
	if(GhostTimer.GetTicks() > GhostTimerTarget) {
		if(GhostTimerTarget == ScatterTime){
            // deenergize pacman
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
	mBlinky.UpdatePos(  mBoard.ActualMap, mPac, TimedStatus);
	mInky.UpdatePos(    mBoard.ActualMap, mPac, mBlinky, TimedStatus);
	mPinky.UpdatePos(   mBoard.ActualMap, mPac, TimedStatus);
	mClyde.UpdatePos(   mBoard.ActualMap, mPac, TimedStatus);

	mPac.UpdatePos(mover, mBoard.ActualMap);	
}

void Game::Food(){
	switch(mPac.FoodCollision(mBoard.ActualMap)){
		case 0:
			mBoard.ScoreIncrease(0);
			mFruit.UpdateFoodCounter();

			if(IsToWakaSound){
				this->mSound.PlayWaka();
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
				this->mSound.PlayWaka();
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
		this->mSound.StopWaka();
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
			this->mSound.PlayScatterGhost();
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

void Game::Update(){
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
		if(mBoard.ActualMap[i] == BlockType::Pellet)
			return false;
		if(mBoard.ActualMap[i] == BlockType::Energizer)
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
	   (mPac.IsColliding(mBlinky) && mBlinky.IsAlive()) ||
	   (mPac.IsColliding(mInky) && mInky.IsAlive()) 	||
	   (mPac.IsColliding(mPinky) && mPinky.IsAlive())   ||
	   (mPac.IsColliding(mClyde) && mClyde.IsAlive())
	)
	mPac.ModLifeStatement(false);
}

void Game::DeadlyGhostPacColl(Ghost &mGhost){
	if(mPac.IsColliding(mGhost) && mGhost.IsAlive()){
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

bool Game::keyboardProcess() {
    bool ret;
    ret = false;
    // processing of keyboard input
    while(SDL_PollEvent(&event) != 0){
    	if(event.type == SDL_QUIT)
    		ret = true;
    	if(event.key.state == SDL_PRESSED){
    		if((event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d))		mover.push_back(Right);
    		else if((event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)) 	mover.push_back(Up);	
    		else if((event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a))	mover.push_back(Left);	
    		else if((event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s))	mover.push_back(Down);	
    		if(mover.size() > 2)
    			mover.erase(mover.begin() + 1);
    	}
    }
    return ret;
}

bool Game::Process(){
    bool ret = true;

        // pacman is alife
    	if (mPac.IsAlive()) {
            // level uncomplete: pellets and energizers left
    		if(!this->IsLevelCompleted()) {
    			this->Update();
    		}
            // level complete
    		else {
                //  animation not started
    			if(!MapAnimationTimer.isStarted()) {
                    // waiting time
    				if(StartTicksInitial != 2500)
    					StartTicksInitial = 2500;

    		        mPac.ResetCurrentLivingFrame();

    		        mFruit.Despawn();
    		        mFruit.ResetFoodCounter();

    		        mSound.StopWaka();
    		        mSound.StopScatterGhost();

    		        this->ModToWaka(true);

    		        MapAnimationTimer.Start();
    			}
                // animation started
    			else if (MapAnimationTimer.GetTicks() > 2100) {
    				this->ClearMover(mover);
    				this->IncreaseLevel();
    				mFruit.ModCurrentFruit(this->GetLevel());
    				UpdateDifficulty();
    				this->ModStartStatement(false);
    				MapAnimationTimer.Reset();
    				GameTimer.Start();
    				ret = false;
    			}
    		}
    	}
        // pacman is not alive
    	else {
            // some lives left
    		if (mBoard.GetLives() > 0) {
    			if(mPac.IsDeadAnimationEnded()){
    				if(StartTicksInitial != 2500)
    					StartTicksInitial = 2500;
    				this->ClearMover(mover);
    				mPac.ModDeadAnimationStatement(false);
    				mPac.ModLifeStatement(true);
    				mBoard.DecreaseLives();
    				mFruit.Despawn();
    				this->ModToWaka(true);
    				this->ModDeathSoundStatement(true);
    				this->ModStartStatement(false);
    				GameTimer.Restart();
                    Start();
    				ret = false;
    			}
    		}
            // no lives left
    		else {
    			if (mPac.IsDeadAnimationEnded()){
    				this->ModStartStatement(false);
    			}
    		}
    		this->DeathSound();
    	}

	SDL_RenderClear(renderer);

    if (ret) {
	    Draw();
	    SDL_RenderPresent(renderer);
    }

	return ret;
}

void Game::Draw(){
	mBoard.SetHighScore();
	mBoard.SetScore();
	mBoard.Draw(mBoard.ActualMap, MapAnimationTimer);

	if(!IsGameStarted){
	    GameOverTexture.loadFromRenderedText("game  over", Red);
		GameOverTexture.render(9 * BlockSize24, 20 * BlockSize24 - 5);
		return;
	}

	mFruit.Draw();

	if(!MapAnimationTimer.isStarted()){
		mClyde.Draw(    mPac,   GhostTimer, ScatterTime);
		mPinky.Draw(    mPac,   GhostTimer, ScatterTime);
		mInky.Draw(     mPac,   GhostTimer, ScatterTime);
		mBlinky.Draw(   mPac,   GhostTimer, ScatterTime);
		this->DrawLittleScore();
	}

	mPac.Draw();
}
