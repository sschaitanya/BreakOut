//
//  BreakOut.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/21/20.
//

#ifndef BreakOut_hpp
#define BreakOut_hpp
#include "Game.hpp"
#include "Paddle.hpp"
#include "Ball.hpp"
#include "LevelBoundary.hpp"
#include "BreakoutGameLevel.hpp"
#include <vector>

enum BreakOutGameState{
    IN_PLAY = 0,
    IN_SERVE ,
    IN_GAME_OVER
};
class BreakOut : public Game{
    
public:
    virtual void Init(GameController& game_controller) override;
    virtual void Update(u_int32_t dt) override;
    virtual void Draw(Screen& screen) override;
    virtual const std::string& GetName() const override;
private:
    const int NUM_LIVES = 3;
    void ResetGame(size_t toLevel =0);
    
    BreakoutGameLevel& GetCurrentLevel() {return game_levels_[current_level];}
    void SetToServeState();
    
    bool IsBallPassedCutOffY() const;
    
    void ReduceLifeByOne();
    
    bool IsGameOver() const {return lives_<=0;}
    
    float INITIAL_BALL_SPEED =  100.0f;
    const Vec2D INITIAL_BALL_VEL =  Vec2D(100, -100);
    Paddle paddle_;
    Ball ball_;
    LevelBoundary level_boundary_;
    std::vector<BreakoutGameLevel> game_levels_;
    size_t current_level;
    BreakOutGameState game_state;
    int lives_;
    float YCutOff_;
    
};
#endif /* BreakOut_hpp */
