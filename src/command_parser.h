#ifndef KEMTER_COMMAND_PARSER_H
#define KEMTER_COMMAND_PARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <memory>

template <class __Container>
void split_string(const std::string& str, __Container& c, char delim = ' ') {
    std::stringstream ss(str);
    std::string token;
    while(std::getline(ss, token, delim)) {
        c.push_back(token);
    }
}

enum class command_type {
    GET, SET, PUT, DELETE, UNKNOWN
};

struct command
{
    command_type method;
    std::string key;
    std::string value;
};

class command_parser
{
public:
    command_parser() {};
    ~command_parser() {};
    std::unique_ptr<command> parse(std::string& buffer) {
        bool isCommand = buffer.at(0) == '/';

        if(isCommand) {
            std::vector<std::string> commands;
            split_string(buffer, commands);
            
            if(commands.size() != 3) {
                return nullptr;
            }
            auto c = std::unique_ptr<command>{
                new command {
                    parse_command_type(commands[0]),
                    commands[1],
                    commands[2]
                }
            };
            return c;
        }

        return nullptr;
    };
private:
    command_type parse_command_type(std::string& command) {
        if(command == "/GET") {
            return command_type::GET;
        } else if(command == "/SET") {
            return command_type::SET;
        } else if (command == "/PUT") {
            return command_type::PUT;
        } else if(command == "/DEL") {
            return command_type::DELETE;
        } else {
            return command_type::UNKNOWN;
        }
    };
};


#endif