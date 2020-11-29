//
//  InputAction.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/18/20.
//

#ifndef InputAction_hpp
#define InputAction_hpp

#include <functional>
#include <stdint.h>

using InputKey = uint8_t;
using InputState = uint8_t;
using MouseButton = uint8_t;
using InputAction  = std::function<void(uint32_t dt, InputState)>;
struct ButtonAction{
    InputKey key;
    InputAction action;
};
struct MousePosition{
    int32_t x_position,y_position;
};

using MouseMovedAction = std::function<void(const MousePosition& mousePosition)>;
using MouseInputAction = std::function<void(InputState state, const MousePosition& mousePosition)>;

struct MouseButtonAction{
    MouseButton mouse_button;
    MouseInputAction mouse_input_action;
};
#endif /* InputAction_hpp */
