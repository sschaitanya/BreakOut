//
//  LevelBoundary.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/25/20.
//

#include "LevelBoundary.hpp"
#include "Ball.hpp"
LevelBoundary::LevelBoundary(const AARectangle& boundary){
    includer_.Init(boundary, true);
}
bool LevelBoundary::HasCollided(const Ball& ball, BoundaryEdge& edge){
    
    
    for(int i=0;i<NUM_EDGES;i++){
        BoundaryEdge collision_edge = includer_.GetEdge(static_cast<EdgeType>(i));
        if(HasCollidedWithEdge(ball,collision_edge)){
            edge = collision_edge;
            return true;
        }
    }
    //std::cout<<"did not collide";
    return false;
}

bool LevelBoundary::HasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const{
    std::cout<< "ball position: "<< ball.GetPosition();
    std::cout<<"Min Dis "<<edge.edge.MinDistanceFrom(ball.GetPosition());
    
    std::cout<<"Ball radius "<<ball.GetRadius();
    return  edge.edge.MinDistanceFrom(ball.GetPosition()) < ball.GetRadius();
}
