//
//  Shape.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/22/20.
//

#ifndef Shape_hpp
#define Shape_hpp

#include "Vec2D.hpp"
#include <vector>

class Shape
{
public:
    virtual Vec2D GetCenterPoint() const = 0;
    virtual ~Shape() {}
    inline virtual std::vector<Vec2D> GetPoints() const {return mPoints;}
    void MoveBy(const Vec2D& deltaOffset);
protected:
    std::vector<Vec2D> mPoints;
};

#endif /* Shape_hpp */
