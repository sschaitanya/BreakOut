//
//  Paddle.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/22/20.
//

#include "Paddle.hpp"
#include "Ball.hpp"
#include "Screen.hpp"
#include "Utils.hpp"
#include "BoundaryEdge.hpp"
#include <cassert>

void Paddle::Init(const AARectangle &rect, const AARectangle& boundary ){
    Excluder::Init(rect);
    boundary_ = boundary;
    direction_ = 0;
}

void Paddle::Update(uint32_t dt, Ball& ball){
    
    if(GetAARectangle().ContainsPoint(ball.GetPosition())){
        Vec2D point_on_edge;
        ball.MakeFlushWithEdge(GetEdge(BOTTOM_EDGE), point_on_edge, true);
    }
    
    Vec2D dir;

    if(direction_!= 0){
        if((direction_ & PaddleDirection::LEFT)==PaddleDirection::LEFT &&
           (direction_ & PaddleDirection::RIGHT)== PaddleDirection::RIGHT){
            dir = Vec2D::Zero;
        }
        else if(direction_ == PaddleDirection::LEFT){
            dir = LEFT_DIR;
        }
        else{
            dir = RIGHT_DIR;
        }
    }
    Vec2D dx = dir* VELOCITY * MilliSecondsToSeconds(dt);

    MoveBy(dx);
    
    const AARectangle& aa_rect = GetAARectangle();
    if(IsGreaterThanOrEqual(boundary_.GetTopLeftPoint().GetX(), aa_rect.GetTopLeftPoint().GetX())){
        MoveTo(Vec2D(boundary_.GetTopLeftPoint().GetX(),aa_rect.GetTopLeftPoint().GetY()));
    }
    else if(IsGreaterThanOrEqual(aa_rect.GetBottomRightPoint().GetX(), boundary_.GetBottomRightPoint().GetX())){
        MoveTo(Vec2D(boundary_.GetBottomRightPoint().GetX() -aa_rect.GetWidth(), aa_rect.GetTopLeftPoint().GetY()));
    }

}
void Paddle::Draw(Screen& screen){
    screen.Draw(GetAARectangle(), Color::Blue(), true, Color::Blue());
}

bool Paddle::Bounce(Ball& ball){
    
    BoundaryEdge boundary_edge;
    if(HasCollided(ball.GetBoundingRect(), boundary_edge))
    {
        Vec2D point_on_edge;
        ball.MakeFlushWithEdge(boundary_edge, point_on_edge, true);
        if(boundary_edge.edge == GetEdge(TOP_EDGE).edge){
            float edge_length = boundary_edge.edge.Length();
            assert(!IsEqual(edge_length, 0));


            float tx = (point_on_edge.GetX() - boundary_edge.edge.GetP0().GetX())/edge_length;

            if(((tx<= CORNER_BOUNCE_AMT) && ball.GetVelocity().GetX()>0) ||
               (tx>= (1.0f - CORNER_BOUNCE_AMT) && ball.GetVelocity().GetX() <0)){
                ball.SetVelocity(-ball.GetVelocity());
                return true;
            }

        }
        ball.SetVelocity(ball.GetVelocity().Reflect(boundary_edge.normal));
        return true;
    }
    return false;
}
