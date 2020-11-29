//
//  Shape.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/22/20.
//

#include "Shape.hpp"


void Shape::MoveBy(const Vec2D& deltaOffset)
{
    for(Vec2D& point : mPoints)
    {
        point = point + deltaOffset;
    }
}
