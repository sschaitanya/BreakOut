//
//  Game.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/20/20.
//

#ifndef Game_hpp
#define Game_hpp

#include <string>
#include "GameController.hpp"
#include "Screen.hpp"

class Game{
  
public:
    virtual ~Game(){}
    virtual void Init(GameController& game_controller) = 0;
    virtual void Update(u_int32_t dt) = 0;
    virtual void Draw(Screen& screen) = 0;
    virtual const std::string& GetName() const = 0;
    
    
    
    
};

#endif /* Game_hpp */
