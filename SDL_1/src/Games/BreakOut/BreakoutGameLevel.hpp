//
//  BreakoutGameLevel.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/25/20.
//

#ifndef BreakoutGameLevel_hpp
#define BreakoutGameLevel_hpp

#include <vector>
#include <stdint.h>
#include "Block.hpp"
#include "Screen.hpp"
#include "Ball.hpp"
#include "AARectangle.hpp"

class BreakoutGameLevel{
  
public:
    BreakoutGameLevel();
    void Init(const AARectangle& boundary);
    void Load(const std::vector<Block>& blocks);
    void Update(uint32_t dt, Ball& ball);
    void Draw(Screen& screen);
    bool IsLevelComplete() const;
    
    static std::vector<BreakoutGameLevel> LoadLevelsFromFile(const std::string& file_path);
private:
    void CreateDefaultLevel(const AARectangle& boundary);
    std::vector<Block> blocks_;
    static const int BLOCK_WIDTH = 40;
    static const int BLOCK_HEIGHT = 20;
};

#endif /* BreakoutGameLevel_hpp */
