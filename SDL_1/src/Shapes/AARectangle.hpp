//
//  AARectangle.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/22/20.
//

#ifndef AARectangle_hpp
#define AARectangle_hpp

#include "Shape.hpp"
class AARectangle: public Shape
{
public:
    AARectangle();
    AARectangle(const Vec2D& topLeft, unsigned int width, unsigned int height);
    AARectangle(const Vec2D& topLeft, const Vec2D& bottomRight);

    inline void SetTopLeftPoint(const Vec2D& topLeft) {mPoints[0] = topLeft;}
    inline void SetBottomRightPoint(const Vec2D& bottomRight) {mPoints[1] = bottomRight;}

    Vec2D GetTopLeftPoint() const {return mPoints[0];}
    Vec2D GetBottomRightPoint() const {return mPoints[1];}

    float GetWidth() const;
    float GetHeight() const;

    void MoveTo(const Vec2D& position);

    virtual Vec2D GetCenterPoint() const override;

    bool Intersects(const AARectangle& otherRect) const;
    bool ContainsPoint(const Vec2D& point) const;

    static AARectangle Inset(const AARectangle& rect, Vec2D& insets);

    virtual std::vector<Vec2D> GetPoints() const override;
};

#endif /* AARectangle_hpp */
