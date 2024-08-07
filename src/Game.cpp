#include "Game.hpp"

Game::Game() {
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
}

Game::~Game() {
    Ready.free();
    GameOverTexture.free();
}

void Game::ResetGhostsLifeStatement() {
    mBlinky.ModLifeStatement(true);
    mInky.ModLifeStatement(true);
    mPinky.ModLifeStatement(true);
    mClyde.ModLifeStatement(true);
}

void Game::ResetGhostsFacing() {
    mBlinky.ModFacing(0);
    mInky.ModFacing(1);
    mPinky.ModFacing(1);
    mClyde.ModFacing(1);
}

void Game::Start() {
    if (!IsGameStarted) {
        if (this->IsLevelCompleted()) {
            mBoard.CopyBoard(ActualMap);
        }
        mBoard.ResetPosition(mPac);
        mBoard.ResetPosition(mBlinky);
        mBoard.ResetPosition(mInky);
        mBoard.ResetPosition(mPinky);
        mBoard.ResetPosition(mClyde);
        mPac.ChangeEnergyStatus(false);
        this->ResetGhostsLifeStatement();
        this->ResetGhostsFacing();
        mPac.ResetCurrentLivingFrame();
        GhostTimer.Restart();
        IsGameStarted = true;
        GhostTimer.Start();
    }
    Ready.render(11 * BlockSize24, 20 * BlockSize24 - 5);
}

void Game::ModStartStatement(bool NewStartStatement) {
    IsGameStarted = NewStartStatement;
}

void Game::Clock() {
    if (GhostTimer.GetTicks() > GhostTimerTarget) {
        if (GhostTimerTarget == ScatterTime) {
            if (mPac.IsEnergized()) {
                mPac.ChangeEnergyStatus(false);
            }
            TimedStatus = false;
            GhostTimerTarget = ChasingTime;
            GhostTimer.Restart();
        } else if (GhostTimerTarget == ChasingTime) {
            TimedStatus = true;
            GhostTimerTarget = ScatterTime;
            GhostTimer.Restart();
        }
    }
}

void Game::UpdatePositions(std::vector<Position::Direction>& mover, bool TimedStatus) {
    mBlinky.UpdatePos(ActualMap, mPac, TimedStatus);
    mInky.UpdatePos(ActualMap, mPac, mBlinky, TimedStatus);
    mPinky.UpdatePos(ActualMap, mPac, TimedStatus);
    mClyde.UpdatePos(ActualMap, mPac, TimedStatus);
    mPac.UpdatePos(mover, ActualMap);
}

void Game::Food() {
    switch (mPac.FoodCollision(ActualMap)) {
        case 0:
            mBoard.ScoreIncrease(0);
            mFruit.UpdateFoodCounter();
            if (IsToWakaSound) {
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
            if (IsToWakaSound) {
                mSound.PlayWaka();
                IsToWakaSound = false;
            }
            WakaTimer.Reset();
            break;
        default:
            if (!WakaTimer.isStarted())
                WakaTimer.Start();
            break;
    }
    if (WakaTimer.GetTicks() > 300) {
        mSound.StopWaka();
        IsToWakaSound = true;
    }
}

void Game::EntityCollisions() {
    if (!mPac.IsEnergized()) {
        this->DeadlyPacGhostColl();
        if (!IsToScatterSound) {
            DeadGhostsCounter = 0;
            mSound.StopScatterGhost();
            IsToScatterSound = true;
        }
    } else {
        if (IsToScatterSound) {
            mSound.PlayScatterGhost();
            IsToScatterSound = false;
        }
        this->DeadlyGhostPacColl(mBlinky);
        this->DeadlyGhostPacColl(mInky);
        this->DeadlyGhostPacColl(mPinky);
        this->DeadlyGhostPacColl(mClyde);
        if (DeadGhostsCounter == 4) {
            if (!IsToScatterSound) {
                mSound.StopScatterGhost();
            }
        }
    }
    if (mFruit.IsEatable()) {
        if (mPac.IsColliding(mFruit)) {
            mFruit.StartScoreTimer();
            mBoard.ScoreIncrease(mFruit.GetScoreValue());
            mFruit.Despawn();
            mSound.PlayEatFruit();
        } else {
            if (mFruit.CheckDespawn())
                mFruit.Despawn();
        }
    }
}

void Game::Update(std::vector<Position::Direction>& mover) {
    this->Clock();
    this->UpdatePositions(mover, TimedStatus);
    this->Food();
    if (mBoard.IsExtraLife())
        mSound.PlayExtraLife();
    this->EntityCollisions();
}

unsigned short Game::GetLevel() {
    return Level;
}

void Game::IncreaseLevel() {
    Level++;
}

void Game::UpdateDifficulty() {
    if (Level % 3 == 0) {
        ChasingTime += 1000;
        if (ScatterTime > 2000) {
            ScatterTime -= 1000;
        }
    }
}

bool Game::IsLevelCompleted() {
    for (unsigned short i = 0; i < BoardHeight * BoardWidth; i++) {
        if (ActualMap[i] == Entity::BlockType::Pellet)
            return false;
        if (ActualMap[i] == Entity::BlockType::Energizer)
            return false;
    }
    return true;
}

void Game::ClearMover(std::vector<Position::Direction>& mover) {
    while (!mover.empty())
        mover.erase(mover.begin());
    mover.push_back((Position::Direction)0);
}

void Game::DeadlyPacGhostColl() {
    if ((mPac.IsColliding(mBlinky) && mBlinky.IsAlive()) || (mPac.IsColliding(mInky) && mInky.IsAlive())
        || (mPac.IsColliding(mPinky) && mPinky.IsAlive()) || (mPac.IsColliding(mClyde) && mClyde.IsAlive()))
        mPac.ModLifeStatement(false);
}

void Game::DeadlyGhostPacColl(Ghost& mGhost) {
    if (mPac.IsColliding(mGhost) && mGhost.IsAlive()) {
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

void Game::ModToWaka(bool NewWaka) {
    IsToWakaSound = NewWaka;
}

void Game::DeathSound() {
    if (IsToDeathPacSound) {
        mSound.StopWaka();
        mSound.PlayPacDeath();
        IsToDeathPacSound = false;
    }
}

void Game::ModDeathSoundStatement(bool NewDeathSoundStatement) {
    IsToDeathPacSound = NewDeathSoundStatement;
}

void Game::DrawLittleScore() {
    for (unsigned char i = 0; i < LittleScoreTimer.size(); i++) {
        Timer ThisLilTimer = LittleScoreTimer.at(i);
        if (ThisLilTimer.GetTicks() < LittleTimerTarget) {
            LTexture ThisLilTexture;
            std::stringstream ss;
            ss << LittleScoreScorers.at(i);
            ThisLilTexture.loadFromRenderedText(ss.str(), White, 1);
            Position ThisLilPos = LittleScorePositions.at(i);
            ThisLilTexture.render(ThisLilPos.GetX(), ThisLilPos.GetY() - BlockSize24 / 2);
            ThisLilTexture.free();
        } else {
            LittleScoreScorers.erase(LittleScoreScorers.begin() + i);
            LittleScoreTimer.erase(LittleScoreTimer.begin() + i);
            LittleScorePositions.erase(LittleScorePositions.begin() + i);
        }
    }
}

bool Game::Process(Timer& GameTimer, std::vector<Position::Direction>& mover, unsigned short& StartTicks) {
    // Returns false when should render the last animation frame.
    // It's bad looking, so I don't want to render it.
    if (GameTimer.GetTicks() < StartTicks) {
        this->Start();
    } else {
        if (mPac.IsAlive()) {
            if (!this->IsLevelCompleted()) {
                this->Update(mover);
            } else {
                if (!MapAnimationTimer.isStarted()) {
                    if (StartTicks != 2500)
                        StartTicks = 2500;
                    mPac.ResetCurrentLivingFrame();
                    mFruit.Despawn();
                    mFruit.ResetFoodCounter();
                    mSound.StopWaka();
                    mSound.StopScatterGhost();
                    this->ModToWaka(true);
                    MapAnimationTimer.Start();
                } else if (MapAnimationTimer.GetTicks() > 2100) {
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
        } else {
            if (mBoard.GetLives() > 0) {
                if (mPac.IsDeadAnimationEnded()) {
                    if (StartTicks != 2500)
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
            } else {
                if (mPac.IsDeadAnimationEnded()) {
                    this->ModStartStatement(false);
                }
            }
            this->DeathSound();
        }
    }
    return true;
}

void Game::Draw() {
    mBoard.SetHighScore();
    mBoard.SetScore();
    mBoard.Draw(ActualMap, MapAnimationTimer);
    if (!IsGameStarted) {
        GameOverTexture.render(9 * BlockSize24, 20 * BlockSize24 - 5);
        return;
    }
    mFruit.Draw();
    if (!MapAnimationTimer.isStarted()) {
        mClyde.Draw(mPac, GhostTimer, ScatterTime);
        mPinky.Draw(mPac, GhostTimer, ScatterTime);
        mInky.Draw(mPac, GhostTimer, ScatterTime);
        mBlinky.Draw(mPac, GhostTimer, ScatterTime);
        this->DrawLittleScore();
    }
    mPac.Draw();
}
