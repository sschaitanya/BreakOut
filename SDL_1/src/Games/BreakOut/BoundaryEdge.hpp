//
//  BoundaryEdge.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/22/20.
//

#ifndef BoundaryEdge_hpp
#define BoundaryEdge_hpp

#include "Vec2D.hpp"
#include "Line2D.hpp"

enum EdgeType{
    BOTTOM_EDGE = 0,
    TOP_EDGE,
    LEFT_EDGE,
    RIGHT_EDGE,
    NUM_EDGES
};
static const Vec2D UP_DIR = {0,-1};
static const Vec2D DOWN_DIR = {0,1};
static const Vec2D LEFT_DIR = {-1,0};
static const Vec2D RIGHT_DIR = {1,0};
struct BoundaryEdge{
    Vec2D normal;
    Line2D edge;
    
};

#endif /* BoundaryEdge_hpp */
