//
//  BreakOut.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/21/20.
//
#include "GameController.hpp"
#include "BreakOut.hpp"
#include "AARectangle.hpp"
#include "App.hpp"
#include "Vec2D.hpp"
#include "Circle.hpp"
#include <iostream>

using namespace std;
void BreakOut::Init(GameController& game_controller){
    

    game_controller.ClearAll();
  
    ResetGame();
    
    ButtonAction serve_action;
    serve_action.key = GameController::ActionKey();
    serve_action.action = [this](uint32_t dt, InputState state){
        if(game_state == IN_SERVE){
            if(GameController::IsPressed(state)){
                game_state = IN_PLAY;
                
                if(paddle_.IsMovingLeft()){
                    ball_.SetVelocity(Vec2D(-INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
                }
                else{
                    ball_.SetVelocity(Vec2D(INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
                }
            }
        }
        else if (game_state == IN_GAME_OVER){
            if(GameController::IsPressed(state)){
                ResetGame();
            }
        }
        };
    
    game_controller.AddInputActionForKey(serve_action);
    
    ButtonAction left_key_action;
    left_key_action.key = GameController::LeftKey();
    left_key_action.action = [this](uint32_t dt, InputState input_state){
        
        if(game_state == IN_PLAY || game_state == IN_SERVE){
            if(GameController::IsPressed(input_state)){
                paddle_.SetMovementDirection(PaddleDirection::LEFT);
            }
            else{
                paddle_.UnSetMovementDirection(PaddleDirection::LEFT);
            }
        }
        
        if(GameController::IsPressed(input_state)){
            std::cout<<"left key pressed";
            paddle_.SetMovementDirection(PaddleDirection::LEFT);
        }
        else{
            paddle_.UnSetMovementDirection(PaddleDirection::LEFT);
        }
    };
    game_controller.AddInputActionForKey(left_key_action);
    
    
    ButtonAction right_key_action;
    right_key_action.key = GameController::RightKey();
    right_key_action.action = [this](uint32_t dt, InputState input_state){
        
        if(game_state == IN_PLAY || game_state == IN_SERVE){
            if(GameController::IsPressed(input_state)){
                paddle_.SetMovementDirection(PaddleDirection::RIGHT);
            }
            else{
                paddle_.UnSetMovementDirection(PaddleDirection::RIGHT);
            }
        }
        
        if(GameController::IsPressed(input_state)){
            std::cout<<"right key pressed";
            paddle_.SetMovementDirection(PaddleDirection::RIGHT);
        }
        else{
            paddle_.UnSetMovementDirection(PaddleDirection::RIGHT);
        }
    };
    game_controller.AddInputActionForKey(right_key_action);
    
}
void BreakOut::Update(u_int32_t dt){
    
    if(game_state == IN_SERVE){
        paddle_.Update(dt, ball_);
        SetToServeState();
    }
    else if(game_state == IN_PLAY){
        ball_.Update(dt);
        paddle_.Update(dt, ball_);
        BoundaryEdge edge;
        
        if(paddle_.Bounce(ball_))
        {
            return;
        }
        
        if(level_boundary_.HasCollided(ball_, edge)){
            ball_.Bounce(edge);
            return;
        }
        GetCurrentLevel().Update(dt, ball_);
        if(IsBallPassedCutOffY()){
            ReduceLifeByOne();
            if(!IsGameOver()){
                SetToServeState();
            }
            else{
                game_state = IN_GAME_OVER;
            }
        }
        else if(GetCurrentLevel().IsLevelComplete()){
            current_level = (current_level+1)% game_levels_.size();
            ResetGame(current_level);
        }
    }
}
void BreakOut::Draw(Screen& screen){
    ball_.Draw(screen);
    paddle_.Draw(screen);
    GetCurrentLevel().Draw(screen);
    screen.Draw(level_boundary_.GetRectangle(),Color::White());
    
    Circle life_circle = {Vec2D(10, App::Singleton().Height() -10), 5};
    
    Line2D cut_off = {Vec2D(0,YCutOff_), Vec2D(App::Singleton().Width(), YCutOff_)};
    screen.Draw(cut_off, Color::White());
    for(int i=0;i<lives_;i++){
        screen.Draw(life_circle, Color::Red(), true, Color::Red());
        life_circle.MoveBy(Vec2D(17,0));
    }
}
const string&  BreakOut::GetName() const{
    static string name = "Break Out!";
    return name;
}

void BreakOut::ResetGame(size_t to_level){
    game_levels_ = BreakoutGameLevel::LoadLevelsFromFile(App::GetBasePath()+ "Assets/BreakoutLevels.txt");
    YCutOff_ = App::Singleton().Height() - 2*Paddle::PADDLE_HEIGHT;
    lives_ = NUM_LIVES;
    current_level = to_level;
//    AARectangle paddleRect = {Vec2D(App::Singleton().Width()/2 - Paddle::PADDLE_WIDTH/2, App::Singleton().Height() - 3*Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT};
    
//    cout<<"start w "<< App::Singleton().Width()/2;
//    cout<<"start h "<< App::Singleton().Height();
    std::cout<<"base path"<<App::GetBasePath();
    current_level = 0;
    
    AARectangle paddle_rect = {Vec2D(App::Singleton().Width()/2 - Paddle::PADDLE_WIDTH/2, App::Singleton().Height() - 3*Paddle::PADDLE_HEIGHT), Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT};
    AARectangle level_boundary = {Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height()};
    level_boundary_ = {level_boundary};
    paddle_.Init(paddle_rect, level_boundary);
    ball_.MoveTo(Vec2D(App::Singleton().Width()/2, App::Singleton().Height() * 0.75f));
    
    //ball_.SetVelocity(INITIAL_BALL_VEL);
    //GetCurrentLevel().Init(level_boundary);
    SetToServeState();
}

void BreakOut::SetToServeState(){
    game_state = IN_SERVE;
    ball_.Stop();
    ball_.MoveTo(Vec2D(
                       paddle_.GetAARectangle().GetCenterPoint().GetX(),
                       paddle_.GetAARectangle().GetTopLeftPoint().GetY() - ball_.GetRadius()-1
                       ));
}

bool BreakOut::IsBallPassedCutOffY() const{
    return ball_.GetPosition().GetY() > YCutOff_;
}

void BreakOut::ReduceLifeByOne(){
    if(lives_>0){
        --lives_;
    }
}
