//
//  Color.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/17/20.
//

#ifndef Color_hpp
#define Color_hpp

#include <stdint.h>
struct SDL_PixelFormat;
class Color{
    uint32_t mColor;
public:
    
    static const SDL_PixelFormat* mFormat;
    static void  InitColorFormat(const SDL_PixelFormat* format);
    
    static Color Black(){return Color(0,0,0,255);}
    static Color White(){return Color(255,255,255,255);}
    static Color Blue(){return Color(0,0,255,255);}
    static Color Red(){return Color(255,0,0,255);}
    static Color Green(){return Color(0,255,0,255);}
    static Color Yellow(){return Color(0,255,0,255);}
    static Color Magenta(){return Color(255,0,255,255);}
    static Color Cyan(){return Color(37,240,217,255);}
    static Color Pink(){return Color(252,197,224,255);}
static Color Tint(){return Color(245,190,100,255);}
    
    Color(): mColor(0){}
    Color(uint32_t color): mColor(color){}
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    
    inline bool operator== (const Color& c) const {return mColor==c.mColor;}
    inline bool operator!= (const Color& c) const {return !(*this == c);}
    inline uint32_t GetPixelColor() const {return mColor;}
    
    void SetRGBA(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a);
  
    void SetRed(u_int8_t red);
    void SetGreen(u_int8_t green);
    void SetBlue(u_int8_t blue);
    void SetAlpha(u_int8_t alpha);


    u_int8_t GetRed() const;
    u_int8_t GetGreen() const;
    u_int8_t GetBlue() const;
    u_int8_t GetAlpha() const;
    
};
#endif /* Color_hpp */
