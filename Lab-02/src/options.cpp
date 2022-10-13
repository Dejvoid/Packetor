#include "options.hpp"
#include <iostream>

bool process_value_option(const std::string& name, const std::string& value){
    bool result = true;
    if(value.empty()){
        std::cout << "Value option <" << value << "> detected but its value is missing!" << std::endl;
        result = false;
        return result;
        }
    std::cout << "Value option <" << name << "> detected with value <" << value << ">" << std::endl;
    return result;
}

bool process_unknown_option(const std::string& name){
    bool result = false;
    std::cout << "Unknown option <" << name << "> found!" << std::endl;
    return result;
}

bool process_flag_option(const std::string& name){
    bool result = true;
    std::cout << "Flag option <" << name << "> detected" << std::endl;
    return result;
}

bool process_arguments(const args_t& args){
    bool result = true;
    for (auto it = args.begin(); it != args.end(); ++it){
        const std::string& s = *it;
        if(s.substr(0, 2) == "--"){
            auto name = s.substr(2);
            if(name == "grayscale" || name == "transparent"){
                result &= process_flag_option(name);
            }
            else if(name == "red" || name == "green" || name == "blue" || name == "alpha"){
                result &= process_value_option(name);
            }
            else{
                result &= process_unknown_option(name);
            }
        }
        else if(s[0] == '-'){
            for (size_t i = 1; i < s.size(); ++i){
                switch (s[i]){
                case 'x':
                    result &= process_flag_option(std::string(1,s[i]));
                case 'y':
                    result &= process_flag_option(std::string(1,s[i]));
                    break;
                case 'r':
                    result &= process_value_option(std::string(1,s[i]), "");
                case 'g':
                    result &= process_value_option(std::string(1,s[i]), "");
                case 'b':
                    result &= process_value_option(std::string(1,s[i]), "");
                case 'a':
                    result &= process_value_option(std::string(1,s[i]), "");
                    //++it;
                    break;
                default:
                    result &= process_unknown_option(std::string(1,s[i]));
                    break;
                }
            }
        }
    }
    return result;
}
