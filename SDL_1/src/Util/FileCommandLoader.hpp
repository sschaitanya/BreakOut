//
//  FileCommandLoader.hpp
//  SDL_1
//
//  Created by santhosh chaitanya singaraju on 10/21/20.
//

#ifndef FileCommandLoader_hpp
#define FileCommandLoader_hpp


#include <functional>
#include <string>
#include <vector>
#include <stdint.h>
#include "Color.hpp"
#include "Vec2D.hpp"
using namespace std;
enum CommandType{
    COMMAND_ONE_LINE = 0,
    COMMAND_MULTI_LINE
};

struct ParseFuncParameters{
   
    string line;
    size_t delimit_position;
    uint32_t line_num;

};

using ParseFunction =function<void(const ParseFuncParameters& params)>;

struct Command{
    CommandType commandType = COMMAND_ONE_LINE;
    string command = "";
    ParseFunction parseFunction = nullptr;
};


class FileCommandLoader{
public:
    void AddCommand(const Command& command);
    bool LoadFile(const string& file_path);
    
    static Color ReadColor(const ParseFuncParameters& params);
    static Vec2D ReadSize(const ParseFuncParameters& params);
    static int ReadInt(const ParseFuncParameters& params);
    static string ReadString(const ParseFuncParameters& params);
    static char ReadChar(const ParseFuncParameters& params);
private:
    vector<Command> commands_;
};

#endif /* FileCommandLoader_hpp */
