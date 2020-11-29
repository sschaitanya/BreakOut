//
//  ScreenBuffer.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/17/20.
//

#ifndef ScreenBuffer_hpp
#define ScreenBuffer_hpp
#include <stdint.h>
#include "Color.hpp"

struct SDL_Surface;

class ScreenBuffer
{
public:
    ScreenBuffer();
    ScreenBuffer(const ScreenBuffer& screenBuffer);
    ~ScreenBuffer();
    ScreenBuffer& operator=(const ScreenBuffer& screenBuffer);

    void Init(uint32_t format, u_int32_t width, u_int32_t h);
    inline SDL_Surface * GetSurface(){return _surface;}
    void Clear(const Color& c = Color::Black());
    void SetPixel(const Color&, int x, int y);
    
private:
    SDL_Surface* _surface;
    uint32_t GetIndex(int r, int c);
    
};
#endif /* ScreenBuffer_hpp */
