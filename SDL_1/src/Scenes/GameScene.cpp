//
//  GameScene.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/20/20.
//

#include "GameScene.hpp"
using namespace std;

GameScene::GameScene(unique_ptr<Game> game){
    game_ = move(game);
}
void GameScene::Init(){
    game_->Init(game_controller_);
}
void GameScene::Update(uint32_t dt){
    game_->Update(dt);
}
void GameScene::Draw(Screen& screen){
    game_->Draw(screen);
}
const string& GameScene::GetSceneName() const{
    return game_->GetName();
}
