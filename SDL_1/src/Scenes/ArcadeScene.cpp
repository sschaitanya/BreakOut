//
//  ArcadeScene.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/18/20.
//
#include "ArcadeScene.hpp"
#include "Screen.hpp"
#include "GameController.hpp"
#include <iostream>
ArcadeScene::ArcadeScene(){
    
}
void ArcadeScene::Init(){
    
    ButtonAction action;
    action.key = GameController::ActionKey();
    action.action = [](uint32_t dt, InputState input_state){
        if(GameController::IsPressed(input_state)){
            std::cout<<"Action button was pressed"<<std::endl;
        }
    };
    game_controller_.AddInputActionForKey(action);
    
    //add for mouse input
    MouseButtonAction mouse_button_action;
    mouse_button_action.mouse_button = GameController::LeftMouseButton();
    mouse_button_action.mouse_input_action = [](InputState input_state, const MousePosition& mouse_position){
        if(GameController::IsPressed(input_state)){
            std::cout<<"Left Mouse button was pressed"<<std::endl;
        }
    };
    
    game_controller_.AddMouseButtonAction(mouse_button_action);
    game_controller_.SetMouseMovedAction([] (const MousePosition& mouse_position){
        std::cout<<"x_pos"<<mouse_position.x_position<<", y_pos"<<mouse_position.y_position;
    });
}
void ArcadeScene::Update(u_int32_t dt){
}
void ArcadeScene::Draw(Screen& theScreen){
    Line2D line = {Vec2D(0,0), Vec2D(theScreen.Width(), theScreen.Height())};
    theScreen.Draw(line, Color::White());
}
const std::string& ArcadeScene::GetSceneName() const{
    static std::string scene_name = "Arcade Scene";
    return scene_name;
}


unique_ptr<Scene> ArcadeScene::GetScene(eGame game){
    switch(game)
    {
        case BREAK_OUT:
        {
            
        }
        break;
        default:{
            
        }
        break;
    }
    return nullptr;
}

