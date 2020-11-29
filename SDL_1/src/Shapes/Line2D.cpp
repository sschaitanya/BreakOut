//
//  Line2D.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/17/20.
//

#include "Line2D.hpp"
#include "Utils.hpp"
#include <cmath>
Line2D::Line2D() {
    Line2D(Vec2D::Zero, Vec2D::Zero);
}
Line2D::Line2D(float x0, float y0, float x1, float y1):Line2D(Vec2D(x0, y0), Vec2D(x1, y1)){
   
}
Line2D::Line2D(const Vec2D& p0, const Vec2D& p1){
    p0_ = p0;
    p1_ = p1;
}

bool Line2D::operator==(const Line2D& line) const{
    return line.GetP0() == p0_ && line.GetP1()==p1_;
}

float Line2D::Slope() const{
    float dx = p1_.GetX() - p0_.GetX();
    if(fabsf(dx) < EPSILON){
        return 0;
    }
    float dy = p1_.GetY() - p0_.GetY();
    
    return dy/dx;
}

Vec2D Line2D::MidPoint() const{
    return Vec2D((p0_.GetX() +p1_.GetX())/2.0f, (p0_.GetY() +p1_.GetY())/2.0f);
}


float Line2D::MinDistanceFrom(const Vec2D& p, bool limitToSegment) const{
    return p.Distance(ClosestPoint(p, limitToSegment));
}

Vec2D Line2D::ClosestPoint(const Vec2D&p, bool limitToSegment ) const{
    Vec2D p0ToP = p - p0_;
    Vec2D p0ToP1 = p1_ - p0_;
    float l2 = p0ToP1.Mag2();
    float dot = p0ToP.Dot(p0ToP1);
    float t = dot / l2;
    if(limitToSegment){
        t = std::fmax(0, std::fmin(1.0f, t));
    }
    return p0_ + p0ToP1 * t;
    
}




float Line2D::Length() const{
    return p1_.Distance(p0_);
}
