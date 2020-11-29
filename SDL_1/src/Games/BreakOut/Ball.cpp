//
//  Ball.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/24/20.
//

#include "Ball.hpp"
#include "Utils.hpp"
#include "Screen.hpp"
#include "Circle.hpp"
#include "BoundaryEdge.hpp"

const float Ball::RADIUS = 10.0f;

Ball::Ball():Ball(Vec2D::Zero, 10.0f){
    
}

//Ball::Ball(const Vec2D& pos, float radius):bounding_box_(pos - Vec2D(radius, radius), radius*2.0f, radius*2.0f), velocity_(Vec2D::Zero)
//{
//
//}

Ball::Ball(const Vec2D& pos, float radius){
    bounding_box_ = AARectangle(pos- Vec2D(radius, radius), radius*2.0f, radius*2.0f);
    velocity_ = Vec2D::Zero;
}
void Ball::Update(uint32_t dt){
    bounding_box_.MoveBy(velocity_* MilliSecondsToSeconds(dt));
}
void Ball::Draw(Screen& screen){
    float radius  = GetRadius();
    Circle circle = {bounding_box_.GetCenterPoint(), radius};
    
    screen.Draw(circle, Color::Red(), true, Color::Red());
}

void Ball::MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& point_on_edge, bool limit_to_edge){
    if(edge.normal == DOWN_DIR){
        bounding_box_.MoveTo(Vec2D(bounding_box_.GetTopLeftPoint().GetX() , edge.edge.GetP0().GetY() + edge.normal.GetY()));
    }
    else if (edge.normal == UP_DIR){
        bounding_box_.MoveTo(Vec2D(bounding_box_.GetTopLeftPoint().GetX() , edge.edge.GetP0().GetY() - bounding_box_.GetHeight()));
    }
    else if(edge.normal == RIGHT_DIR){
        bounding_box_.MoveTo(Vec2D(edge.edge.GetP0().GetX() + edge.normal.GetX(),
                             bounding_box_.GetTopLeftPoint().GetY()));
    }
    else if(edge.normal == LEFT_DIR){
        bounding_box_.MoveTo(Vec2D(edge.edge.GetP0().GetX() - bounding_box_.GetWidth(),
                             bounding_box_.GetTopLeftPoint().GetY()));
    }
    
    point_on_edge = edge.edge.ClosestPoint(bounding_box_.GetCenterPoint(), limit_to_edge);
}

void Ball::MoveTo(const Vec2D& point){
    bounding_box_.MoveTo(point - Vec2D(GetRadius(), GetRadius()));
}

void Ball::Bounce(const BoundaryEdge& edge){
    Vec2D  pointOnEdge;
    MakeFlushWithEdge(edge, pointOnEdge, false);
    velocity_ = velocity_.Reflect(edge.normal);
}
