//
//  BreakoutGameLevel.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/25/20.
//

#include "BreakoutGameLevel.hpp"
#include "Ball.hpp"
#include "App.hpp"
#include "FileCommandLoader.hpp"

BreakoutGameLevel::BreakoutGameLevel(){
    
}
void BreakoutGameLevel::Init(const AARectangle& boundary){
    CreateDefaultLevel(boundary);
}
void BreakoutGameLevel::Load(const std::vector<Block>& blocks){
    blocks_.clear();
    blocks_ = blocks;
}
void BreakoutGameLevel::Update(uint32_t dt, Ball& ball){
    std::vector<Block> collided_blocks;
    BoundaryEdge edge_to_bounce_off_of;
    Block* block_to_bounce_off_of = nullptr;
    float largest_magnitude = -1.0f;
    for(auto& block: blocks_){
        BoundaryEdge edge;
        if(block.IsDestroyed()==false && block.HasCollided(ball.GetBoundingRect(), edge)){
            std::cout<<"block collided";
            collided_blocks.push_back(block);
            float mag = block.GetCollisionOffset(ball.GetBoundingRect()).Mag();
            if(mag > largest_magnitude){
                edge_to_bounce_off_of = edge;
                block_to_bounce_off_of = &block;
            }
        }
    }
    
    if(block_to_bounce_off_of != nullptr){
        block_to_bounce_off_of->Bounce(ball, edge_to_bounce_off_of);
        block_to_bounce_off_of->ReduceHitPoint();
    }
    
    for(const auto& block: collided_blocks){
        BoundaryEdge edge;
        if(block.HasCollided(ball.GetBoundingRect(), edge)){
            Vec2D p;
            ball.MakeFlushWithEdge(edge, p, true);
        }
    }
    
}
void BreakoutGameLevel::Draw(Screen& screen){
    for(auto& block: blocks_){
        if(block.IsDestroyed()==false){
            block.Draw(screen);
        }
    }
}

void BreakoutGameLevel::CreateDefaultLevel(const AARectangle& boundary){
    blocks_.clear();
    
    const int NUM_BLOCKS_ACROSS = ((int)boundary.GetWidth() - (2*(BLOCK_WIDTH))/BLOCK_WIDTH);
    const int NUM_BLOCK_ROWS = 5;
    
    float startX = ((int)boundary.GetWidth() - (NUM_BLOCKS_ACROSS * (BLOCK_WIDTH+1)))/2;
    
    Color colors[NUM_BLOCK_ROWS];
    colors[0] = Color::Red();
    colors[1] = Color::Magenta();
    colors[2] = Color::Yellow();
    colors[3] = Color::Green();
    colors[4] = Color::Cyan();
    
    for(int r = 0; r< NUM_BLOCK_ROWS; ++r){
        AARectangle block_rect = {Vec2D(startX, BLOCK_HEIGHT* (r+1)), BLOCK_WIDTH, BLOCK_HEIGHT};
        for(int c=0; c< NUM_BLOCKS_ACROSS; ++c){
            Block b;
            b.Init(block_rect, 1, Color::Black(), colors[r]);
            blocks_.push_back(b);
            block_rect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
        }
    }
}

bool BreakoutGameLevel::IsLevelComplete() const{
    for(size_t i=0;i< blocks_.size() ;i++){
        if(blocks_[i].IsDestroyed()==false &&
           blocks_[i].GetHitPoint() != Block::UNBREAKABLE){
            return false;
        }
    }
    return true;
}


struct LayoutBlock{
    char symbol = '-';
    int hp = 0;
    Color color = Color::Black();
};


LayoutBlock FindLayoutBlockForSymbol(const std::vector<LayoutBlock>& blocks, char symbol){
    for(int i=0; i< blocks.size(); ++i){
        if(blocks[i].symbol == symbol){
            return blocks[i];
        }
    }
    return LayoutBlock();
}

std::vector<BreakoutGameLevel> BreakoutGameLevel::LoadLevelsFromFile(const std::string& file_path){
    std::vector<BreakoutGameLevel> levels;
    std::vector<LayoutBlock> layout_blocks;
    std::vector<Block> level_blocks;
    int width = 0;
    int height = 0;
    FileCommandLoader file_loader;
    
    Command level_command;
    level_command.command = "level";
    level_command.parseFunction = [&](ParseFuncParameters params){
        if(levels.size()>0){
            levels.back().Load(level_blocks);
        }
        layout_blocks.clear();
        level_blocks.clear();
        width = 0;
        height = 0;
        
        BreakoutGameLevel level;
        level.Init(AARectangle(Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height()));
        levels.push_back(level);
    };
    file_loader.AddCommand(level_command);
    
    Command block_command;
    block_command.command = "block";
    block_command.parseFunction =[&](ParseFuncParameters params){
        LayoutBlock lb;
        layout_blocks.push_back(lb);
    };
    file_loader.AddCommand(block_command);

    Command symbol_command;
    symbol_command.command = "symbol";
    symbol_command.parseFunction = [&](ParseFuncParameters params){
        layout_blocks.back().symbol = FileCommandLoader::ReadChar(params);
    };
    file_loader.AddCommand(symbol_command);

    Command fill_color_command;
    fill_color_command.command = "fillcolor";
    fill_color_command.parseFunction = [&](ParseFuncParameters params){
        layout_blocks.back().color = FileCommandLoader::ReadColor(params);
    };
    file_loader.AddCommand(fill_color_command);
    
    Command hit_point_command;
    hit_point_command.command = "hp";
    hit_point_command.parseFunction = [&](ParseFuncParameters params){
        layout_blocks.back().hp = FileCommandLoader::ReadInt(params);
    };
    file_loader.AddCommand(hit_point_command);
    
    Command width_command;
    width_command.command = "width";
    width_command.parseFunction = [&](ParseFuncParameters params){
        width = FileCommandLoader::ReadInt(params);
    };
    file_loader.AddCommand(width_command);
    
    Command height_command;
    height_command.command = "height";
    height_command.parseFunction = [&](ParseFuncParameters params){
        height = FileCommandLoader::ReadInt(params);
    };
    file_loader.AddCommand(height_command);
    
    Command layout_command;
    layout_command.commandType = COMMAND_MULTI_LINE;
    layout_command.command = "layout";
    layout_command.parseFunction = [&](ParseFuncParameters params){
        
        int block_width = BLOCK_WIDTH;
        int screen_width = App::Singleton().Width();
        
        float block_starting_pos = 0;
        //static_cast<float>(screen_width - block_width*width) /2.0f;
        AARectangle block_rect(Vec2D(block_starting_pos, (params.line_num+1)*BLOCK_HEIGHT),
                               BLOCK_WIDTH, BLOCK_HEIGHT);
        
        for(int c=0; c< params.line.length(); ++c)
        {
            if(params.line[c]!= '-'){
                LayoutBlock layout_block = FindLayoutBlockForSymbol(layout_blocks, params.line[c]);
                Block b;
                b.Init(block_rect, layout_block.hp, Color::Black() , layout_block.color);
                level_blocks.push_back(b);
            }
            block_rect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
        }
    };

    file_loader.AddCommand(layout_command);
    file_loader.LoadFile(file_path);
    
    if(levels.size() > 0){
        levels.back().Load(level_blocks);
    }
    
    return levels;
}
