//
//  ArcadeScene.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/18/20.
//

#ifndef ArcadeScene_hpp
#define ArcadeScene_hpp

#include "Scene.hpp"
#include <memory>
using namespace std;
enum eGame{
    BREAK_OUT =0
    
};


class ArcadeScene: public Scene
{
public:
    ArcadeScene();
    virtual void Init() override;
    virtual void Update(u_int32_t dt) override;
    virtual void Draw(Screen& theScreen) override;
    virtual const std::string& GetSceneName() const override;
    
    
private:
    unique_ptr<Scene> GetScene(eGame game);
    
};


#endif /* ArcadeScene_hpp */
