//
//  InputController.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/19/20.
//

#ifndef InputController_hpp
#define InputController_hpp

#include "InputAction.hpp"

class GameController;

class InputController{
public:
    InputController();
    void Init(InputAction quitAction);
    void Update(uint32_t dt);
    void SetGameController(GameController* controller);

private:
    InputAction quit_;
    GameController* current_controller_;
};
#endif /* InputController_hpp */
