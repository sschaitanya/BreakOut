//
//  Block.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/25/20.
//

#include "Block.hpp"
#include "Screen.hpp"
#include "Ball.hpp"
Block::Block(){
    outline_color_ = Color::White();
    fill_color_ = Color::White();
    hit_point_ = 1;
}
void Block::Init(const AARectangle& rect, int hit_point, const Color& outline_color, const Color& fill_color){
    Excluder::Init(rect);
    hit_point_ = hit_point;
    outline_color_ = outline_color;
    fill_color_ = fill_color;
}

void Block::Draw(Screen& screen){
    screen.Draw(GetAARectangle(), outline_color_, true, fill_color_);
}

void Block::Bounce(Ball& ball, const BoundaryEdge& edge){
    ball.Bounce(edge);
}

void Block::ReduceHitPoint(){
    if(hit_point_>0) --hit_point_;
}
