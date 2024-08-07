#include "Board.hpp"

static const char* CharBoard = "                            "
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
                               "######.##### ## #####.######"
                               "     #.##### ## #####.#     "
                               "     #.##    1     ##.#     "
                               "     #.## ###==### ##.#     "
                               "######.## #      # ##.######"
                               "      .   #2 3 4 #   .      "
                               "######.## #      # ##.######"
                               "     #.## ######## ##.#     "
                               "     #.##          ##.#     "
                               "     #.## ######## ##.#     "
                               "######.## ######## ##.######"
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

Board::Board() {
    MapTexture.loadFromFile("Textures/Map24.png");
    PelletTexture.loadFromFile("Textures/Pellet24.png");
    EnergizerTexture.loadFromFile("Textures/Energizer24.png");
    DoorTexture.loadFromFile("Textures/Door.png");
    LivesTexture.loadFromFile("Textures/Lives32.png");
    ScoreWordTexture.loadFromRenderedText("Score", White);
    HighScoreWordTexture.loadFromRenderedText("High Score", White);
    MapTexture.setColor(0x00, 0x00, 0xff);
    this->ConvertSketch();
    Score = 0;
    IsExtra = false;
    Lives = 4;
}

Board::~Board() {
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

void Board::ConvertSketch() {
    for (unsigned short i = 0; i < BoardHeight * BoardWidth; i++) {
        switch (CharBoard[i]) {
            case '#':
                NumericBoard[i] = Entity::BlockType::Wall;
                break;
            case '=':
                NumericBoard[i] = Entity::BlockType::Door;
                break;
            case '.':
                NumericBoard[i] = Entity::BlockType::Pellet;
                break;
            case 'o':
                NumericBoard[i] = Entity::BlockType::Energizer;
                break;
            default:
                NumericBoard[i] = Entity::BlockType::Nothing;
                break;
        }
    }
}

void Board::ResetPosition(Entity& mEntity) {
    char y = -1;
    for (unsigned short i = 0; i < BoardHeight * BoardWidth; i++) {
        unsigned char x = i % BoardWidth;
        if (x == 0)
            y++;
        if (CharBoard[i] == '0' && mEntity.GetIdentity() == Entity::EntityType::ePacMan) {
            mEntity.ModX(x * BlockSize24 + BlockSize24 / 2);
            mEntity.ModY(y * BlockSize24);
            return;
        } else if (CharBoard[i] == '1' && mEntity.GetIdentity() == Entity::EntityType::eBlinky) {
            mEntity.ModX(x * BlockSize24 + BlockSize24 / 2);
            mEntity.ModY(y * BlockSize24);
            return;
        } else if (CharBoard[i] == '2' && mEntity.GetIdentity() == Entity::EntityType::eInky) {
            mEntity.ModX(x * BlockSize24 + BlockSize24 / 2);
            mEntity.ModY(y * BlockSize24);
            return;
        } else if (CharBoard[i] == '3' && mEntity.GetIdentity() == Entity::EntityType::ePinky) {
            mEntity.ModX(x * BlockSize24 + BlockSize24 / 2);
            mEntity.ModY(y * BlockSize24);
            return;
        } else if (CharBoard[i] == '4' && mEntity.GetIdentity() == Entity::EntityType::eClyde) {
            mEntity.ModX(x * BlockSize24 + BlockSize24 / 2);
            mEntity.ModY(y * BlockSize24);
            return;
        }
    }
}

void Board::SetScore() {
    std::stringstream ss;
    ss << Score;
    ScoreTexture.loadFromRenderedText(ss.str(), White);
}

void Board::SetHighScore() {
    unsigned int High;
    std::ifstream HighScores("HighScore.txt");
    HighScores >> High;
    std::stringstream ss;
    if (Score > High) {
        ss << Score;
        std::ofstream HighScores("HighScore.txt");
        HighScores << ss.str();
    } else
        ss << High;
    HighScoreTexture.loadFromRenderedText(ss.str(), White);
    HighScores.close();
}

void Board::Draw(unsigned char ActualMap[], Timer MapAnimationTimer) {
    ScoreWordTexture.render();
    ScoreTexture.render(0, BlockSize32);
    HighScoreWordTexture.render(336);
    HighScoreTexture.render(336, BlockSize32);
    MapTexture.render();
    for (unsigned char i = 1; i <= Lives; i++) {
        LivesTexture.render(i * BlockSize32, 26 * BlockSize32 - BlockSize32 / 4);
    }
    if (!MapAnimationTimer.isStarted()) {
        DoorTexture.render(WindowWidth / 2 - 23, WindowHeight / 2 - 57);
        char y = -1;
        for (unsigned short i = 0; i < BoardHeight * BoardWidth; i++) {
            unsigned char x = i % BoardWidth;
            if (x == 0)
                y++;
            if (ActualMap[i] == Entity::BlockType::Pellet)
                PelletTexture.render(x * BlockSize24, y * BlockSize24);
            if (ActualMap[i] == Entity::BlockType::Energizer)
                EnergizerTexture.render(x * BlockSize24, y * BlockSize24);
        }
    } else {
        if ((MapAnimationTimer.GetTicks() / 250) % 2 == 1)
            MapTexture.setColor(255, 255, 255);
        else
            MapTexture.setColor(0, 0, 255);
    }
}

void Board::CopyBoard(unsigned char ActualMap[]) {
    memcpy(ActualMap, NumericBoard, BoardHeight * BoardWidth);
}

bool Board::IsExtraLife() {
    if (!IsExtra && Score >= 10000) {
        IsExtra = true;
        Lives++;
        return true;
    }
    return false;
}

void Board::IncreaseLives() {
    Lives++;
}

void Board::DecreaseLives() {
    Lives--;
}

unsigned char Board::GetLives() {
    return Lives;
}

void Board::ScoreIncrease(unsigned short Scorer) {
    switch (Scorer) {
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
