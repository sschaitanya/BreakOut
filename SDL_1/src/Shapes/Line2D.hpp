//
//  Line2D.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/17/20.
//

#ifndef Line2D_hpp
#define Line2D_hpp
#include "Vec2D.hpp"
#include <stdio.h>
class Line2D{
public:
    Line2D();
    Line2D(float x0, float y0, float x1, float y1);
    Line2D(const Vec2D& p0, const Vec2D& p1);
    
    inline const Vec2D& GetP0() const{
        return p0_;
    }
    inline const Vec2D& GetP1() const{
        return p1_;
    }
    
    inline void SetP0(const Vec2D& p0){ p0_ = p0;}
    inline void SetP1(const Vec2D& p1){ p1_ = p1;}
    
    bool operator==(const Line2D& line) const;
    
    float MinDistanceFrom(const Vec2D& p, bool limitToSegment  = false) const;
    Vec2D ClosestPoint(const Vec2D& p, bool limitToSegment  = false) const;
    
    Vec2D MidPoint() const;
    float Slope() const;
    float Length() const;
    
private:
    Vec2D p0_;
    Vec2D p1_;
};
#endif /* Line2D_hpp */
