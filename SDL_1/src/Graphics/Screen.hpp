//
//  Screen.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/17/20.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <stdint.h>
#include "SDL.h"
#include "ScreenBuffer.hpp"
#include "Color.hpp"
#include "Line2D.hpp"
#include "AARectangle.hpp"
#include "Circle.hpp"

class Vec2D;
struct SDL_Window;
class Screen{

public:
    Screen();
    ~Screen();
    
    SDL_Window* Init(uint32_t w, uint32_t h, uint32_t mag);
    void SwapScreen();
    
    inline void SetClearColor(const Color& clearColor){clear_color_ = clearColor;}
    inline uint32_t Width() const {return width_;}
    inline uint32_t Height() const {return height_;}
    
    //Draw Methods
    void Draw(int x, int y, const Color& color);
    void Draw(const Vec2D& point, const Color& color);
    void Draw(const Line2D& line, const Color& color);
    void Draw(const AARectangle& rect, const Color& color, bool fill = false, const Color& fillColor = Color::White());
    void Draw(const Circle& circle, const Color& color, bool fill = false, const Color& fillColor = Color::White());
    
private:
    void FillPoly(const std::vector<Vec2D>& points, const Color& color);
    Screen(const Screen& screen);
    Screen& operator=(const Screen& screen);
    void ClearScreen();
    
    u_int32_t width_;
    u_int32_t height_;
    Color clear_color_;
    ScreenBuffer back_buffer_;
    SDL_Window* window_;
    SDL_Surface* surface_;
    
};

#endif /* Screen_hpp */
