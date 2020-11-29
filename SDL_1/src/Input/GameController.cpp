//
//  GameController.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/18/20.
//

#include "GameController.hpp"
#include <SDL.h>
GameController::GameController(){
    mouse_moved_action_ = nullptr;
}
InputAction GameController::GetActionForKey(InputKey key){
    for(const auto& buttonAction: button_actions_){
        if(key == buttonAction.key){
            return buttonAction.action;
        }
    }
    return [](u_int32_t, InputState){};
}

void GameController::AddInputActionForKey(const ButtonAction& buttonAction)
{
    button_actions_.push_back(buttonAction);
}

void GameController::ClearAll(){
    button_actions_.clear();
}


bool GameController::IsPressed(InputState state){
    return state == SDL_PRESSED;
}

bool GameController::IsReleased(InputState state){
    return state == SDL_RELEASED;
}
InputKey GameController::ActionKey(){
    return static_cast<InputKey>(SDLK_a);
}
InputKey GameController::CancelKey(){
    return static_cast<InputKey>(SDLK_s);
}
InputKey GameController::RightKey(){
    return static_cast<InputKey>(SDLK_RIGHT);
}
InputKey GameController::LeftKey(){
    return static_cast<InputKey>(SDLK_LEFT);
}
InputKey GameController::UpKey(){
    return static_cast<InputKey>(SDLK_UP);
}
InputKey GameController::DownKey(){
    return static_cast<InputKey>(SDLK_DOWN);
}

MouseInputAction GameController::GetMouseButtonActionForMouseButton(MouseButton mouse_button){
    for(const auto& button_action: mouse_button_actions_){
        if(mouse_button == button_action.mouse_button){
            return button_action.mouse_input_action;
        }
    }
    return [](InputState state, const MousePosition& pos){};
}

void GameController::AddMouseButtonAction(const MouseButtonAction& mouse_button_action){
    mouse_button_actions_.push_back(mouse_button_action);
}

MouseButton GameController::LeftMouseButton(){
    return static_cast<MouseButton>(SDL_BUTTON_LEFT);
}
MouseButton GameController::RightMouseButton(){
    return static_cast<MouseButton>(SDL_BUTTON_RIGHT);
}

