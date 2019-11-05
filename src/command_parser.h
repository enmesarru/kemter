#ifndef KEMTER_COMMAND_PARSER_H
#define KEMTER_COMMAND_PARSER_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <memory>
#include <variant>
#include "kemter_types.h"
#include "kemterdb.h"

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

    std::string execute(command& cmd, kemterdb& db_) {
        std::string response = "";
        
        if(cmd.method == command_type::UNKNOWN) {
            return "Unknown method type.";
        } else if(cmd.method == command_type::GET) {
            kemter::type::TypeWrapper wrapper = db_.get(cmd.key);

            std::visit(
                kemter::type::base_visitor(
                    [&](kemter::type::Type<std::string> s) { 
                        response = "/GET -S " + cmd.key + " " + s.value();
                    },
                    [&](auto &&) { response = "Unknown data type."; }
                ), wrapper);
                
        } else if(cmd.method == command_type::SET) {
            db_.add(cmd.key, cmd.value);
            response = "/SET -S " + cmd.key ;
        } else if(cmd.method == command_type::PUT) {
            db_.put(cmd.key, cmd.value);
            response = "/PUT -S " + cmd.key;
        } else if(cmd.method == command_type::DELETE) {
            bool done = db_.remove(cmd.key);
            response = "/DEL -S";
        }

        return response;
    }

    std::unique_ptr<command> parse(std::string& buffer) {
        bool isCommand = buffer.at(0) == '/';

        if(isCommand) {
            std::vector<std::string> commands;
            split_string(buffer, commands);

            command_type cmd_type = parse_command_type(commands[0]);
            
            if(cmd_type == command_type::GET) {
                auto get_cmd = std::unique_ptr<command>{
                    new command { cmd_type, commands[1], commands[2] }
                };
                return get_cmd;
            } else if(cmd_type == command_type::SET) {
                auto set_cmd = std::unique_ptr<command>{
                    new command { cmd_type, commands[1], commands[2] }
                };
                return set_cmd;
            } else if(cmd_type == command_type::PUT) {
                auto put_cmd = std::unique_ptr<command>{
                    new command { cmd_type, commands[1], commands[2] }
                };
                return put_cmd;
            } else if(cmd_type == command_type::DELETE) {
                auto delete_cmd = std::unique_ptr<command>{
                    new command { cmd_type, commands[1] }
                };
                return delete_cmd;
            } else {
                auto unknown_cmd = std::unique_ptr<command>{
                    new command { cmd_type }
                };
                return unknown_cmd;
            }
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