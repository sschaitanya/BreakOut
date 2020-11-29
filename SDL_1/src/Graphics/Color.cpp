//
//  Color.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/17/20.
//

#include "Color.hpp"
#include "SDL.h"

 const SDL_PixelFormat* Color::mFormat= nullptr;
void  Color::InitColorFormat(const SDL_PixelFormat* format){
    Color::mFormat = format;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
    SetRGBA(r, g, b,a);
}

void Color:: SetRGBA(uint8_t r, u_int8_t g, u_int8_t b, u_int8_t a){
    mColor = SDL_MapRGBA(mFormat, r, g, b, a);
}

void Color::SetRed(u_int8_t red){
    u_int8_t r;
    u_int8_t g;
    u_int8_t b;
    u_int8_t a;
    SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
    SetRGBA(red,g,b,a);
}
void Color::SetGreen(u_int8_t green){
    u_int8_t r;
    u_int8_t g;
    u_int8_t b;
    u_int8_t a;
    SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
    SetRGBA(r,green,b,a);
}
void Color::SetBlue(u_int8_t blue){
    u_int8_t r;
    u_int8_t g;
    u_int8_t b;
    u_int8_t a;
    SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
    SetRGBA(r,g,blue,a);
}

void Color::SetAlpha(u_int8_t alpha){
    u_int8_t r;
    u_int8_t g;
    u_int8_t b;
    u_int8_t a;
    SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
    SetRGBA(r,g,b,alpha);
}

u_int8_t Color::GetRed() const{
    u_int8_t r;
    u_int8_t g;
    u_int8_t b;
    u_int8_t a;
    SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
    return r;
}
u_int8_t Color::GetGreen() const{
    u_int8_t r;
    u_int8_t g;
    u_int8_t b;
    u_int8_t a;
    SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
    return g;
}
u_int8_t Color::GetBlue() const{
    u_int8_t r;
    u_int8_t g;
    u_int8_t b;
    u_int8_t a;
    SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
    return b;
}
u_int8_t Color::GetAlpha() const{
    u_int8_t r;
    u_int8_t g;
    u_int8_t b;
    u_int8_t a;
    SDL_GetRGBA(mColor, mFormat, &r, &g, &b, &a);
    return a;
}
