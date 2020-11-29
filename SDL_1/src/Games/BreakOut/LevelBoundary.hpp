//
//  LevelBoundary.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/25/20.
//

#ifndef LevelBoundary_hpp
#define LevelBoundary_hpp

#include "Excluder.hpp"
#include "Ball.hpp"
class LevelBoundary{
public:
    LevelBoundary(){}
    LevelBoundary(const AARectangle& boundary);
    bool HasCollided(const Ball& ball, BoundaryEdge& edge);
    inline const AARectangle& GetRectangle() const
    {return includer_.GetAARectangle();}
private:
    bool HasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const;
    Excluder includer_;
    
};
#endif /* LevelBoundary_hpp */
