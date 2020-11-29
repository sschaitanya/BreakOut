//
//  Block.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/25/20.
//

#ifndef Block_hpp
#define Block_hpp
#include "Excluder.hpp"
#include "Color.hpp"
#include "Ball.hpp"
#include "Screen.hpp"
#include "BoundaryEdge.hpp"
class Block: public Excluder{
public:
    Block();
    static const int UNBREAKABLE = -1;
    void Init(const AARectangle& rect, int hp, const Color& outline_color, const Color& fill_color);
    void Draw(Screen& screen);
    void Bounce(Ball& bounce, const BoundaryEdge& edge);
    
    void ReduceHitPoint();
    inline int GetHitPoint() const {return hit_point_;}
    inline bool IsDestroyed() const {return hit_point_ == 0;}
    inline const Color& GetOutLineColor() const {return outline_color_;}
    inline const Color& GetFillColor() const {return fill_color_;}

private:
    Color outline_color_;
    Color fill_color_;
    int hit_point_;
};




#endif /* Block_hpp */
