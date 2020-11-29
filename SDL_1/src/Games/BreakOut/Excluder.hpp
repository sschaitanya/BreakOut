//
//  Excluder.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/22/20.
//

#ifndef Excluder_hpp
#define Excluder_hpp

#include "AARectangle.hpp"
#include "BoundaryEdge.hpp"

class Excluder{
    
public:
    virtual ~Excluder() {}
    void Init(const AARectangle& rect, bool reverse_normals = false);
    bool HasCollided(const AARectangle& rect, BoundaryEdge& edge) const;
    Vec2D GetCollisionOffset(const AARectangle& rect) const;
    inline const AARectangle& GetAARectangle() const {return aa_rectangle_;}
    void MoveBy(const Vec2D& delta);
    void MoveTo(const Vec2D& point);
    const BoundaryEdge& GetEdge(EdgeType edge) const;
    
private:
    void SetUpEdges();
    AARectangle aa_rectangle_;
    BoundaryEdge boundary_edges_[NUM_EDGES];
    bool reverse_normals_;
};

#endif /* Excluder_hpp */
