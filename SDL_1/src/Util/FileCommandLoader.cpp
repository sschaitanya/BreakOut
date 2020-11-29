//
//  FileCommandLoader.cpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/21/20.
//

#include "FileCommandLoader.hpp"
#include <fstream>
#include <iostream>
#include "Color.hpp"
#include "Vec2D.hpp"

using namespace std;

void FileCommandLoader::AddCommand(const Command& command){
    commands_.push_back(command);
}
bool FileCommandLoader::LoadFile(const string& file_path){
    ifstream in_file;
   
    in_file.open(file_path);
    string line = "";
    if(!in_file.is_open()){
        cout<<"could not open the file";
    }
    while(!in_file.eof()){
        getline(in_file, line);
        size_t command_pos = string::npos;
        if((command_pos = line.find(":"))!=string::npos){
            size_t delimit_pos = line.find_first_of(" ", command_pos);
            if(delimit_pos == string::npos){
                delimit_pos = line.length();
            }
            else{
                delimit_pos-=1;
            }
            string command_str = line.substr(command_pos+1, delimit_pos);
            delimit_pos+=1;
            
            for(size_t command_index=0; command_index<commands_.size();++command_index){
                if(command_str==commands_[command_index].command){
                    if(commands_[command_index].commandType == COMMAND_ONE_LINE){
                        
                       // ParseFuncParameters parameters(line, delimit_pos,0);
                        ParseFuncParameters parameters;
                        parameters.delimit_position = delimit_pos;
                        parameters.line_num = 0;
                        parameters.line = line;
                        std::cout<< parameters.delimit_position<<endl;
                        std::cout<< parameters.line<<endl;
                        std::cout<< parameters.line_num<<endl;
                        std::cout<< commands_[command_index].command<<endl;
                        std::cout<< commands_[command_index].commandType<<endl;
                 
                        commands_[command_index].parseFunction(parameters);
                    }
                    else{
                        string num_lines = line.substr(delimit_pos+1);
                        int total_lines = stoi(num_lines);
                        int line_num = 0;
                        while(line_num< total_lines){
                            getline(in_file, line);
                            if(line.empty()) continue;
                            else{
                                ParseFuncParameters parameters;
                                //ParseFuncParameters parameters(line, 0,line_num);
//                                ParseFuncParameters parameters;
                                parameters.delimit_position = 0;
                                parameters.line_num = line_num;
                                parameters.line = line;
                                commands_[command_index].parseFunction(parameters);
                                ++line_num;

                            }
                        }
                    }
                    
                }
            }
            
        }
    }
    return true;
    
}

 Color FileCommandLoader::ReadColor(const ParseFuncParameters& params){
     size_t next_space_pos = params.line.find_first_of(" ", params.delimit_position+1);
     int r = stoi(params.line.substr(params.delimit_position, (next_space_pos-params.delimit_position)));
     size_t last_space_pos = next_space_pos;
     next_space_pos = params.line.find_first_of(" ", last_space_pos+1);
     int g = stoi(params.line.substr(last_space_pos+1, (next_space_pos-last_space_pos)));
     last_space_pos = next_space_pos;
     next_space_pos = params.line.find_first_of(" ", last_space_pos+1);
     int b = stoi(params.line.substr(last_space_pos+1, (next_space_pos-last_space_pos)));
     int a = stoi(params.line.substr(next_space_pos+1));
     
     return Color(r,g,b,a);
}
 Vec2D FileCommandLoader::ReadSize(const ParseFuncParameters& params){
     size_t next_space_pos = params.line.find_first_of(" ", params.delimit_position+1);
     int width = stoi(params.line.substr(params.delimit_position, (next_space_pos-params.delimit_position)));
     size_t last_space_pos = next_space_pos;
     next_space_pos = params.line.find_first_of(" ", last_space_pos+1);
     int height = stoi(params.line.substr(last_space_pos+1, (next_space_pos-last_space_pos)));
     
     return Vec2D(width, height);
}
 int FileCommandLoader::ReadInt(const ParseFuncParameters& params){
     string int_str = params.line.substr(params.delimit_position+1);
     return stoi(int_str);
}
string FileCommandLoader::ReadString(const ParseFuncParameters& params){
    return params.line.substr(params.delimit_position+1);
}
 char FileCommandLoader::ReadChar(const ParseFuncParameters& params){
     return params.line.substr(params.delimit_position+1)[0];
}
