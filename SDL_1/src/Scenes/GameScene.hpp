//
//  GameScene.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/20/20.
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include "Scene.hpp"
#include "Game.hpp"
using namespace std;
class GameScene: public Scene
{
public:
    GameScene(unique_ptr<Game> game);
    virtual ~GameScene(){}
    virtual void Init() override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& screen) override;
    virtual const string& GetSceneName() const override;
    
private:
    unique_ptr<Game> game_;
    
};

#endif /* GameScene_hpp */
