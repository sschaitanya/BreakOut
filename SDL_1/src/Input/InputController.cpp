//
//  InputController.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/19/20.
//

#include "InputController.hpp"
#include <SDL.h>
#include "GameController.hpp"
InputController::InputController(){
    quit_ = nullptr;
    current_controller_ = nullptr;
}
void InputController::InputController::Init(InputAction quitAction){
    quit_ = quitAction;
}
void InputController::Update(uint32_t dt){
    SDL_Event sdl_event;
    while(SDL_PollEvent(&sdl_event)){
        switch(sdl_event.type){
            case SDL_QUIT:
                quit_(dt, SDL_PRESSED);
            case SDL_MOUSEMOTION:
                if(current_controller_){
                    if(MouseMovedAction mouse_moved_action = current_controller_->GetMouseMovedAction()){
                        MousePosition position;
                        position.x_position = sdl_event.motion.x;
                        position.y_position = sdl_event.motion.y;
                        mouse_moved_action(position);
                    }
                }
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
                if(current_controller_){
                    MouseInputAction mouse_input_action = current_controller_->
                    GetMouseButtonActionForMouseButton(static_cast<MouseButton>(sdl_event.button.button));
                    MousePosition mouse_position;
                    mouse_position.x_position = sdl_event.button.x;
                    mouse_position.y_position = sdl_event.button.y;
                    mouse_input_action(static_cast<InputState>(sdl_event.button.state), mouse_position);
                }
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                if(current_controller_){
                    InputAction action = current_controller_->GetActionForKey(sdl_event.key.keysym.sym);
                    action(dt, static_cast<InputState>(sdl_event.key.state));
                }
                break;
        }
    }
}
void InputController::SetGameController(GameController* controller){
    current_controller_ = controller;
}
