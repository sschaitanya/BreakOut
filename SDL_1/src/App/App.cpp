//
//  App.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/17/20.
//

#include "App.hpp"
#include "Line2D.hpp"
#include "SDL.h"
#include "Color.hpp"
#include "ArcadeScene.hpp"
#include "GameScene.hpp"
#include "BreakOut.hpp"

using namespace std;
App& App::Singleton(){
    static App theApp;
    return theApp;
}
bool App::Init(uint32_t width, uint32_t height, uint32_t mag){
    window_ = screen_.Init(width, height, mag);
    
    std::unique_ptr<ArcadeScene> arcade_scene = std::make_unique<ArcadeScene>();
        
    PushScene(std::move(arcade_scene));
    //Temp
    {
        unique_ptr<BreakOut> break_out_game = make_unique<BreakOut>();
        unique_ptr<GameScene> break_out_scene = make_unique<GameScene>(move(break_out_game));
        PushScene(move(break_out_scene));
    }
    return window_!=nullptr;
}

void App::Run(){
    if(window_){
        
        //theScreen.Draw(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, Color::Yellow());
        //screen_.SwapScreen();
        
        bool running = true;
        
        uint32_t last_tick = SDL_GetTicks();
        uint32_t current_tick = last_tick;
        uint32_t dt = 10;
        uint32_t accumulator = 0;
      
        input_controller_.Init([&running](uint32_t dt, InputState state){
            running = false;
        });
        
        
        while (running)
        {
            current_tick = SDL_GetTicks();
            uint32_t frame_time  = current_tick - last_tick;
            if(frame_time > 1000) frame_time = 1000;
            last_tick = current_tick;
            accumulator += frame_time;
            
            
            //Input
            input_controller_.Update(dt);
            
            Scene* topScene = TopScene();
            
            if(topScene)
            {
                //Update
                while(accumulator >= dt){
                    //update current scene by dt
                    topScene->Update(dt);
                    //std::cout<< "Delta time step"<<dt <<std::endl;
                    accumulator -=dt;
                }
            }
       
            //Render
            topScene->Draw(screen_);
            screen_.SwapScreen();
        }
    }
}


void App::PushScene(std::unique_ptr<Scene> scene){

    if(scene)
    {
        scene->Init();
        input_controller_.SetGameController(scene->GetGameController());
        scene_stack_.emplace_back(std::move(scene));
        SDL_SetWindowTitle(window_, TopScene()->GetSceneName().c_str());
    }
}

void App::PopScene(){
    if(scene_stack_.size() > 1){
        scene_stack_.pop_back();
    }
    if(TopScene()){
        input_controller_.SetGameController(TopScene()->GetGameController());
        SDL_SetWindowTitle(window_, TopScene()->GetSceneName().c_str());
    }

}
Scene* App::TopScene(){
    if(scene_stack_.empty()){
        return nullptr;
    }
    return scene_stack_.back().get();
}

const std::string& App::GetBasePath(){
    static std::string base_path = SDL_GetBasePath();
    return base_path;
}
