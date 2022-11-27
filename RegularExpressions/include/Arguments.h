#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <vector>
#include <string>
#include <fstream>
#include "Regex.h"
#include "Constants.h"

using args_t = std::vector<std::string>;

static inline bool is_switch(const std::string& arg){
    return arg[0] == SWITCH_CHAR;
}

std::vector<std::string> expressions_from_args(const args_t& args){
    bool from_file = false;
    std::vector<std::string> ret;
    for (auto it = args.begin(); it != args.end(); ++it){
        if (is_switch((*it))){
            const std::string& option = *it;
            switch (option[1])
            {
            case ARG_SWITCH:
                from_file = false;
                break;
            case FILE_SWITCH:
                from_file = true;
                break;
            default:
                // ERROR
                break;
            }
        }
        else{
            if (from_file){
                std::ifstream fs;
                fs.open(*it, std::fstream::in);
                if (fs.good()){
                    for (std::string line; std::getline(fs, line);){
                        if (line.length() != 0){
                            ret.push_back(line);
                        }
                    }
                }
            }
            else {
                ret.push_back(*it);
            }
        }
    }
    return ret;
}

#endif