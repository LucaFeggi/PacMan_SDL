
class Board{
	private:
    
    // board walls are draw is not a texture
    // a string, not an array
    const std::string CharBoard =
    	"                            "
    	"                            "
    	"                            "
    	"############################"
    	"#............##............#"
    	"#.####.#####.##.#####.####.#"
    	"#o####.#####.##.#####.####o#"
    	"#.####.#####.##.#####.####.#"
    	"#..........................#"
    	"#.####.##.########.##.####.#"
    	"#.####.##.########.##.####.#"
    	"#......##....##....##......#"
    	"######.#####.##.#####.######"
    	"     #.#####.##.#####.#     "
    	"     #.##....1.....##.#     "
    	"     #.##.###==###.##.#     "
    	"######.##.#      #.##.######"
    	"..........#2 3 4 #.........."
    	"######.##.#      #.##.######"
    	"     #.##.########.##.#     "
    	"     #.##..........##.#     "
    	"     #.##.########.##.#     "
    	"######.##.########.##.######"
    	"#............##............#"
    	"#.####.#####.##.#####.####.#"
    	"#.####.#####.##.#####.####.#"
    	"#o..##.......0 .......##..o#"
    	"###.##.##.########.##.##.###"
    	"###.##.##.########.##.##.###"
    	"#......##....##....##......#"
    	"#.##########.##.##########.#"
    	"#.##########.##.##########.#"
    	"#..........................#"
    	"############################"
    	"                            "
    	"                            ";

        // board wall, dots, pellets, door
		unsigned char NumericBoard[BoardHeight * BoardWidth];

        // board textures
		LTexture MapTexture;
		LTexture PelletTexture;
		LTexture EnergizerTexture;
		LTexture DoorTexture;

		LTexture LivesTexture;
		LTexture ScoreWordTexture;
		LTexture ScoreTexture;
		LTexture HighScoreWordTexture;
		LTexture HighScoreTexture;
        

		unsigned int Score;
		bool IsExtra;
		char Lives;

	public:

        // original board, const
		unsigned char ActualMap[BoardHeight * BoardWidth];
    
    // Constructor
    Board() {

	    MapTexture.loadFromFile("Textures/Map24.png");
        // blue color
	    MapTexture.setColor(0x00, 0x00, 0xff);


	    PelletTexture.loadFromFile("Textures/Pellet24.png");
	    EnergizerTexture.loadFromFile("Textures/Energizer24.png");
	    DoorTexture.loadFromFile("Textures/Door.png");

	    LivesTexture.loadFromFile("Textures/Lives32.png");

	    ScoreWordTexture.loadFromRenderedText("Score", White);
	    HighScoreWordTexture.loadFromRenderedText("High Score", White);


        
        // board
	    this->ConvertSketch();
	    CopyBoard();

	    Score = 0;
	    IsExtra = false;
	    Lives = 4;

    }

	~Board();
    
    // Methods
	void ConvertSketch();
	void ResetPosition(Entity &ThisEntity);

	void CopyBoard();
	void SetScore();
	void SetHighScore();
	bool IsExtraLife();
	void IncreaseLives();
	void DecreaseLives();
	void ScoreIncrease(unsigned short Scorer);
	unsigned char GetLives();
	void Draw(unsigned char ActualMap[], Timer MapAnimationTimer);

};


Board::~Board(){
	MapTexture.free();
	PelletTexture.free();
	EnergizerTexture.free();
	DoorTexture.free();
	LivesTexture.free();
	ScoreWordTexture.free();
	ScoreTexture.free();
	HighScoreWordTexture.free();
	HighScoreTexture.free();
}


//  numeric board from char board
void Board::ConvertSketch() {
	for(unsigned short i = 0; i < BoardHeight * BoardWidth; i++){
		switch(CharBoard[i]){
			case '#':
				NumericBoard[i] = BlockType::Wall;
				break;
			case '=':
				NumericBoard[i] = BlockType::Door;
				break;
			case '.':
				NumericBoard[i] = BlockType::Pellet;
				break;
			case 'o':
				NumericBoard[i] = BlockType::Energizer;
				break;
			default:
				NumericBoard[i] = BlockType::Nothing;
				break;
		}
	}
}


// copies NumericBoard into ActualMap
void Board::CopyBoard(){
	memcpy(ActualMap, NumericBoard, BoardHeight * BoardWidth);
}


// change cell number in a grid representation of a board for cartesian (x,y) coordinates
// for the characters
void Board::ResetPosition(Entity &mEntity){
	char y = -1;

	for(unsigned short i = 0; i < BoardHeight * BoardWidth; i++){
		unsigned char x = i % BoardWidth;

		if (x == 0)
			y++;

		if (CharBoard[i] == '0' && mEntity.GetIdentity() == EntityType::ePacMan){
			mEntity.ModX(x * BlockSize24 + BlockSize24/2);
			mEntity.ModY(y * BlockSize24);
		}
		else if(CharBoard[i] == '1' && mEntity.GetIdentity() == EntityType::eBlinky){
			mEntity.ModX(x * BlockSize24 + BlockSize24/2);
			mEntity.ModY(y * BlockSize24);
		}
		else if(CharBoard[i] == '2' && mEntity.GetIdentity() == EntityType::eInky){
			mEntity.ModX(x * BlockSize24 + BlockSize24/2);
			mEntity.ModY(y * BlockSize24);
		}
		else if(CharBoard[i] == '3' && mEntity.GetIdentity() == EntityType::ePinky){
			mEntity.ModX(x * BlockSize24 + BlockSize24/2);
			mEntity.ModY(y * BlockSize24);
		}
		else if(CharBoard[i] == '4' && mEntity.GetIdentity() == EntityType::eClyde){
			mEntity.ModX(x * BlockSize24 + BlockSize24/2);
			mEntity.ModY(y * BlockSize24);
		}
	}
}







void Board::SetScore(){
	std::stringstream ss;
	ss << Score;
	ScoreTexture.loadFromRenderedText(ss.str(), White);
}

void Board::SetHighScore(){
	unsigned int High;
	std::ifstream HighScores("HighScore.txt");
	HighScores >> High;
	std::stringstream ss;
	if(Score > High){
		ss << Score;
		std::ofstream HighScores ("HighScore.txt");
 		HighScores << ss.str(); 
	}
	else
		ss << High;
	HighScoreTexture.loadFromRenderedText(ss.str(), White);
	HighScores.close();
}





void Board::Draw(unsigned char ActualMap[], Timer MapAnimationTimer) {

	ScoreWordTexture.render();
	ScoreTexture.render(0, BlockSize32);
	HighScoreWordTexture.render(336);
	HighScoreTexture.render(336, BlockSize32);
    
    // rendering map
	MapTexture.render();
    
    // rendering lives
	for(unsigned char i = 1; i <= Lives; i++){
		LivesTexture.render(i * BlockSize32, 26 * BlockSize32 - BlockSize32/4);
	}
    
    // rendering pellets and energizers
    // animation not started
	if(!MapAnimationTimer.isStarted()){

		DoorTexture.render(WindowWidth/2 - 23, WindowHeight/2 - 57);

		char y = -1;
		for(unsigned short i = 0; i < BoardHeight * BoardWidth; i++){
			unsigned char x = i % BoardWidth;
			if(x == 0)
				y++;

			if(ActualMap[i] == BlockType::Pellet)
				PelletTexture.render(x * BlockSize24, y * BlockSize24);

			if(ActualMap[i] == BlockType::Energizer)
				EnergizerTexture.render(x * BlockSize24, y * BlockSize24);
		}
	}
    // animation started
    // code lines below have no effect
	else {	
		if((MapAnimationTimer.GetTicks() / 250) % 2 == 1)
			MapTexture.setColor(255, 255, 255);
		else
			MapTexture.setColor(0, 0, 255);
	}
}






bool Board::IsExtraLife(){
	if(!IsExtra && Score >= 10000){
		IsExtra = true;
		Lives++;
		return true;
	}
	return false;
}

void Board::IncreaseLives(){
	Lives++;
}

void Board::DecreaseLives(){
	Lives--;
}

unsigned char Board::GetLives(){
	return Lives;
}

void Board::ScoreIncrease(unsigned short Scorer){
	switch(Scorer){
		case 0:
			Score += 10;
			break;
		case 1:
			Score += 50;
			break;
		default:
			Score += Scorer;
			break;
	}
}
