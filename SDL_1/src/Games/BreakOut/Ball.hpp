//
//  Ball.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/24/20.
//

#ifndef Ball_hpp
#define Ball_hpp
#include "AARectangle.hpp"
#include "Screen.hpp"
struct BoundaryEdge;
class Ball{
public:
    Ball();
    Ball(const Vec2D& pos, float radius);
    void Update(uint32_t dt);
    void Draw(Screen& screen);
    void MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& point_on_edge, bool limit_to_edge);
    inline void Stop(){velocity_ = Vec2D::Zero;}
    void MoveTo(const Vec2D& point);
    
    inline const AARectangle GetBoundingRect() const{return bounding_box_;};
    
    inline void SetVelocity(const Vec2D& vel) {velocity_ = vel;}
    inline Vec2D GetVelocity() const {return velocity_;}
    inline float GetRadius() const {return bounding_box_.GetWidth()/2.0f;}
    inline Vec2D GetPosition() const {return bounding_box_.GetCenterPoint();}
    
    void Bounce(const BoundaryEdge& edge);
private:
    AARectangle bounding_box_;
    Vec2D velocity_;
    static const float RADIUS;
    
};

#endif /* Ball_hpp */
