//
//  GameController.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/18/20.
//

#ifndef GameController_hpp
#define GameController_hpp

#include "InputAction.hpp"
#include <vector>

class GameController{
public:
    GameController();
    InputAction GetActionForKey(InputKey key);
    void AddInputActionForKey(const ButtonAction& buttonAction);
    void ClearAll();
    static bool IsPressed(InputState state);
    static bool IsReleased(InputState state);
    static InputKey ActionKey();
    static InputKey CancelKey();
    static InputKey RightKey();
    static InputKey LeftKey();
    static InputKey UpKey();
    static InputKey DownKey();
    
    inline MouseMovedAction& GetMouseMovedAction() {return mouse_moved_action_;}
    inline void SetMouseMovedAction(const MouseMovedAction& mouse_moved_action) {this->mouse_moved_action_ = mouse_moved_action;}
    
    MouseInputAction GetMouseButtonActionForMouseButton(MouseButton button);
    void AddMouseButtonAction(const MouseButtonAction& mouse_button_action);
    
    static MouseButton LeftMouseButton();
    static MouseButton RightMouseButton();
private:
    std::vector<ButtonAction> button_actions_;
    std::vector<MouseButtonAction> mouse_button_actions_;
    MouseMovedAction mouse_moved_action_;
};

#endif /* GameController_hpp */
