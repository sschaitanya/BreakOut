//
//  App.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/17/20.
//

#ifndef App_hpp
#define App_hpp

#include "Screen.hpp"
#include <stdint.h>
#include <vector>
#include <memory>
#include "Scene.hpp"
#include "InputController.hpp"
struct SDL_Window;
using namespace std;
class App{
public:
    static App& Singleton();
    bool Init(uint32_t width, uint32_t height, uint32_t mag);
    void Run();
    
    inline uint32_t Width() const {return screen_.Width();}
    inline uint32_t Height() const {return screen_.Height();}
    
    void PushScene(std::unique_ptr<Scene> scene);
    void PopScene();
    Scene* TopScene();
    
    static const std::string& GetBasePath();
private:
    Screen screen_;
    SDL_Window* window_;
    std::vector<unique_ptr<Scene>> scene_stack_;
    InputController input_controller_;
    
};

#endif /* App_hpp */
