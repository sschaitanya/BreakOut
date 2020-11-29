//
//  Scene.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/18/20.
//

#ifndef Scene_hpp
#define Scene_hpp
#include <string>
#include "Screen.hpp"
#include "GameController.hpp"
class Scene{
public:
    virtual ~Scene() {}
    virtual void Init() = 0;
    virtual void Update (uint32_t dt) = 0;
    virtual void Draw(Screen& theScreen)=0;
    virtual const std::string& GetSceneName() const =0;
    GameController* GetGameController() {return &game_controller_;}
    
protected:
    GameController game_controller_;
};


#endif /* Scene_hpp */
