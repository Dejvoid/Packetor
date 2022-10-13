#include "options.hpp"
#include <iostream>

bool process_value_option(const std::string &name, const std::string &value)
{
    bool result = true;
    if (value.length() == 0)
    {
        std::cout << "Value option <" << name << "> detected but its value is missing!" << std::endl;
        result = false;
        return result;
    }
    std::cout << "Value option <" << name << "> detected with value <" << value << ">" << std::endl;
    return result;
}

bool process_unknown_option(const std::string &name)
{
    bool result = false;
    std::cout << "Unknown option <" << name << "> found!" << std::endl;
    return result;
}

bool process_flag_option(const std::string &name)
{
    bool result = true;
    std::cout << "Flag option <" << name << "> detected" << std::endl;
    return result;
}

bool process_standalone_value(const std::string &value)
{
    std::cout << "Standalone value detected <" << value << ">" << std::endl;
    return false;
}

bool process_arguments(const args_t &args)
{
    bool result = true;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        const std::string &s = *it;
        if (s.substr(0, 2) == "--")
        {
            auto name = s.substr(2);
            if (name == "grayscale" || name == "transparent")
            {
                result &= process_flag_option(name);
            }
            else if (name == "red" || name == "green" || name == "blue" || name == "alpha")
            {
                if (it+1 != args.end())
                {
                    const std::string &value = *++it;
                    result &= process_value_option(name, value);
                }
                else
                {
                    result &= process_value_option(name, "");
                    //return result;
                }
            }
            else
            {
                result &= process_unknown_option(name);
                //return result;
            }
        }
        else if (s[0] == '-')
        {
            for (size_t i = 1; i < s.size(); ++i)
            {
                switch (s[i])
                {
                case 'x':
                case 'y':
                case 't':
                    result &= process_flag_option(std::string(1, s[i]));
                    break;
                case 'r':
                case 'g':
                case 'b':
                case 'a':
                    if (s.size() - (i + 1) > 0){
                        result &= process_value_option(std::string(1, s[i]), s.substr(i + 1, s.size()));
                        i = s.size();
                    }
                    else{
                    if (it + 1 != args.end()) {
                        const std::string &value = *++it;
                        result &= process_value_option(std::string(1, s[i]), value);
                    }
                    else{
                        result &= process_value_option(std::string(1, s[i]), "");
                        //return result;
                        }}
                    break;
                default:
                    result &= process_unknown_option(std::string(1, s[i]));
                    //return result;
                    break;
                }
            }
        }
        else
        {
            result &= process_standalone_value(s);
            //return result;
        }
    }
    return result;
}