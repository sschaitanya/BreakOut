//
//  main.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/13/20.
//
#include <iostream>

#include "App.hpp"
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
//const int SCREEN_WIDTH = 224;
//const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 1;
using namespace std;

int main(){
    
    if(App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION)){
        App::Singleton().Run();
    }
  

    return 0;
}


