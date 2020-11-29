//
//  Excluder.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/22/20.
//

#include "Excluder.hpp"
#include "Utils.hpp"
#include <cmath>
#include <cassert>

void Excluder::Init(const AARectangle& rect, bool reverse_normals){
    aa_rectangle_ = rect;
    reverse_normals_ = reverse_normals;
    SetUpEdges();
}
bool Excluder::HasCollided(const AARectangle& rect, BoundaryEdge& edge) const{
    if(aa_rectangle_.Intersects(rect)){
        float y_min = aa_rectangle_.GetTopLeftPoint().GetY() >= (rect.GetTopLeftPoint().GetY())? aa_rectangle_.GetTopLeftPoint().GetY(): rect.GetTopLeftPoint().GetY();
        
        float y_max = aa_rectangle_.GetBottomRightPoint().GetY() <= (rect.GetBottomRightPoint().GetY())? aa_rectangle_.GetBottomRightPoint().GetY(): rect.GetBottomRightPoint().GetY();
        
        float y_size = y_max - y_min;
        
        float x_min = aa_rectangle_.GetTopLeftPoint().GetX() >= (rect.GetTopLeftPoint().GetX())? aa_rectangle_.GetTopLeftPoint().GetX(): rect.GetTopLeftPoint().GetX();
        
        float x_max = aa_rectangle_.GetBottomRightPoint().GetX() <= (rect.GetBottomRightPoint().GetX())? aa_rectangle_.GetBottomRightPoint().GetX(): rect.GetBottomRightPoint().GetX();
        
        float x_size = x_max - x_min;
        
        if(x_size > y_size){
            if(rect.GetCenterPoint().GetY() > aa_rectangle_.GetCenterPoint().GetY()){
                edge = boundary_edges_[BOTTOM_EDGE];
            }
            else{
                edge = boundary_edges_[TOP_EDGE];
            }
        }
        else{
            if(rect.GetCenterPoint().GetX() < aa_rectangle_.GetCenterPoint().GetX()){
                edge = boundary_edges_[LEFT_EDGE];
            }
            else{
                edge = boundary_edges_[RIGHT_EDGE];
            }
        }
        return true;
    }
    return false;
}
Vec2D Excluder::GetCollisionOffset(const AARectangle& rect) const
{
    BoundaryEdge boundary_edge;
    Vec2D offset = Vec2D::Zero;
    
    if(HasCollided(rect, boundary_edge)){
        float y_min = aa_rectangle_.GetTopLeftPoint().GetY() >= (rect.GetTopLeftPoint().GetY())? aa_rectangle_.GetTopLeftPoint().GetY(): rect.GetTopLeftPoint().GetY();
        
        float y_max = aa_rectangle_.GetBottomRightPoint().GetY() <= (rect.GetBottomRightPoint().GetY())? aa_rectangle_.GetBottomRightPoint().GetY(): rect.GetBottomRightPoint().GetY();
        
        float y_size = y_max - y_min;
        
        float x_min = aa_rectangle_.GetTopLeftPoint().GetX() >= (rect.GetTopLeftPoint().GetX())? aa_rectangle_.GetTopLeftPoint().GetX(): rect.GetTopLeftPoint().GetX();
        
        float x_max = aa_rectangle_.GetBottomRightPoint().GetX() <= (rect.GetBottomRightPoint().GetX())? aa_rectangle_.GetBottomRightPoint().GetX(): rect.GetBottomRightPoint().GetX();
        
        float x_size = x_max - x_min;
        
        if(!IsEqual(boundary_edge.normal.GetY(), 0)){
            offset = (y_size+1)*boundary_edge.normal;
        }
        else{
            offset = (x_size+1)*boundary_edge.normal;
        }
    }
    return offset;
}
void Excluder::MoveBy(const Vec2D& delta){
    aa_rectangle_.MoveBy(delta);
    SetUpEdges();
}
void Excluder::MoveTo(const Vec2D& point){
    aa_rectangle_.MoveTo(point);
    SetUpEdges();
}
const BoundaryEdge& Excluder::GetEdge(EdgeType edge) const {
    assert(edge!=NUM_EDGES);
    return boundary_edges_[edge];
}
void Excluder::SetUpEdges(){
 
    boundary_edges_[TOP_EDGE].edge = {
        aa_rectangle_.GetTopLeftPoint().GetX(),
        aa_rectangle_.GetTopLeftPoint().GetY(),
        aa_rectangle_.GetBottomRightPoint().GetX(),
        aa_rectangle_.GetTopLeftPoint().GetY()};
    boundary_edges_[TOP_EDGE].normal = UP_DIR;
    
    boundary_edges_[LEFT_EDGE].edge = {
        aa_rectangle_.GetTopLeftPoint().GetX(),
        aa_rectangle_.GetTopLeftPoint().GetY(),
        aa_rectangle_.GetTopLeftPoint().GetX(),
        aa_rectangle_.GetBottomRightPoint().GetY()};
    boundary_edges_[LEFT_EDGE].normal = LEFT_DIR;
    
    boundary_edges_[BOTTOM_EDGE].edge = {
        aa_rectangle_.GetTopLeftPoint().GetX(),
        aa_rectangle_.GetBottomRightPoint().GetY(),
        aa_rectangle_.GetBottomRightPoint().GetX(),
        aa_rectangle_.GetBottomRightPoint().GetY()};
    boundary_edges_[BOTTOM_EDGE].normal = DOWN_DIR;
    
    
    boundary_edges_[RIGHT_EDGE].edge = {
        aa_rectangle_.GetBottomRightPoint().GetX(),
        aa_rectangle_.GetTopLeftPoint().GetY(),
        aa_rectangle_.GetBottomRightPoint().GetX(),
        aa_rectangle_.GetBottomRightPoint().GetY()};
    boundary_edges_[RIGHT_EDGE].normal = RIGHT_DIR;
    
   
    
    if(reverse_normals_){
        for(auto& edge: boundary_edges_){
            edge.normal = -edge.normal;
        }
    }
    }

