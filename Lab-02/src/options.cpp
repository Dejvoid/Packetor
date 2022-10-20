#include "options.hpp"
#include <iostream>

bool write_value_info(const std::string &name, const std::string &value)
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

bool process_flag_option(const std::string &name, bool *option_exists)
{
    *option_exists = true;
    bool result = true;
    std::cout << "Flag option <" << name << "> detected" << std::endl;
    return result;
}

bool process_standalone_value(const std::string &value, options_t &options)
{
    options.values.push_back(value);
    std::cout << "Standalone value detected <" << value << ">" << std::endl;
    return false;
}

void write_int_error(const std::string &value)
{
    std::cout << "Value <" << value << "> is not a valid integer number!" << std::endl;
}

void write_float_error(const std::string &value)
{
    std::cout << "Value <" << value << "> is not a valid floating point number!" << std::endl;
}

bool process_int_option(const std::string &name, const std::string &value, std::string &out_value, options_t &options)
{
    size_t p; // returns index after matched
    try
    {
        int result = std::stoi(value, &p);
        if (p - value.length() > 0)
        {
            write_int_error(value);
            options.flag_r = false;
            return false;
        }
        out_value = std::to_string(result);
        if (name == "r" || name == "red")
        {
            options.flag_r = true;
            options.value_r = result;
        }
        if (name == "g" || name == "green")
        {
            options.flag_g = true;
            options.value_g = result;
        }
        if (name == "b" || name == "blue")
        {
            options.flag_b = true;
            options.value_g = result;
        }
    }
    catch (...)
    {
        // some error occured
        write_int_error(value);
        return false;
    }
    return true;
}

bool process_float_option(const std::string &name, const std::string &value, std::string &out_value, options_t &options)
{
    size_t p;
    try
    {
        float result = std::stof(value, &p);
        if (p - value.length() > 0)
        {
            write_float_error(value);
            options.flag_a = false;
            return false;
        }
        
        out_value = std::to_string(result);
        if (name == "a" || name == "alpha")
        {
            options.flag_a = true;
            options.value_a = result;
        }
    }
    catch (...)
    {
        write_float_error(value);
        return false;
    }
    return true;
}

bool process_long_option(const std::string &name, const args_t &args, args_t::const_iterator &it, options_t &options)
{
    bool result = true;
    if (name == "grayscale")
    {
        result &= process_flag_option(name, &options.flag_gs);
    }
    else if (name == "transparent")
    {
        result &= process_flag_option(name, &options.flag_t);
    }
    else if (name == "red" || name == "green" || name == "blue")
    {
        std::string out_value;
        if (it + 1 != args.end())
        {
            const std::string &value = *++it;
            bool temp_res = process_int_option(name, value, out_value, options);
            if(temp_res){
                write_value_info(name, out_value);
            }
            result &= temp_res;
        }
        else
        {
            result &= process_int_option(name, "", out_value, options);
        }
    }
    else if (name == "alpha")
    {
        std::string out_value;
        if (it + 1 != args.end())
        {
            const std::string &value = *(++it);
            bool temp_res = process_float_option(name, value, out_value, options);
            if(temp_res){
                write_value_info(name, out_value);
            }
            result &= temp_res;
        }
        else
        {
            result &= process_float_option(name, "", out_value, options);
        }
    }
    else
    {
        result &= process_unknown_option(name);
    }
    return false;
}

bool process_short_option(const std::string &s, size_t &i, args_t::const_iterator &it, const args_t &args, options_t &options)
{
    bool result = true;
    std::string out_value;
    std::string name = std::string(1, s[i]);
    switch (s[i])
    {
    case 'x':
        result &= process_flag_option(name, &options.flag_x);
        break;
    case 'y':
        result &= process_flag_option(name, &options.flag_y);
        break;
    case 't':
        result &= process_flag_option(name, &options.flag_t);
        break;
    case 'r':
    case 'g':
    case 'b':
    {
        if (s.size() - (i + 1) > 0)
        {
            bool temp_res = process_int_option(name, s.substr(i + 1, s.size()), out_value, options);
            if (temp_res)
            {
                write_value_info(name, out_value);
            }
            result &= temp_res;
            i = s.size();
        }
        else
        {
            if (it + 1 != args.end())
            {
                const std::string &value = *++it;
                bool temp_res = process_int_option(name, value, out_value, options);
                if (temp_res)
                {
                    write_value_info(name, out_value);
                }
                result &= temp_res;
            }
            else
            {
                bool temp_res = process_int_option(name, "", out_value, options);
                if (temp_res)
                {
                    write_value_info(name, out_value);
                }
                result &= temp_res;
            }
            
        }
    }
    break;
    case 'a':
    {
        if (s.size() - (i + 1) > 0)
        {
            bool temp_res = process_float_option(name, s.substr(i + 1, s.size()), out_value, options);
            if (temp_res)
            {
                write_value_info(name, out_value);
            }
            result &= temp_res;
            i = s.size();
        }
        else
        {
            if (it + 1 != args.end())
            {
                const std::string &value = *++it;
                bool temp_res = process_float_option(name, value, out_value, options);
                if (temp_res)
                {
                    write_value_info(name, out_value);
                }
                result &= temp_res;
            }
            else
            {
                bool temp_res = process_float_option(name, "", out_value, options);
                if (temp_res)
                {
                    write_value_info(name, out_value);
                }
                result &= temp_res;
            }
        }
    }
    break;
    default:
        result &= process_unknown_option(name);
        break;
    }
    return false;
}

bool process_arguments(const args_t &args, options_t &options)
{
    bool result = true;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
        const std::string &s = *it;
        if (s.substr(0, 2) == "--")
        {
            auto name = s.substr(2);
            result &= process_long_option(name, args, it, options);
        }
        else if (s[0] == '-')
        {
            for (size_t i = 1; i < s.size(); ++i)
            {
                result &= process_short_option(s, i, it, args, options);
            }
        }
        else
        {
            result &= process_standalone_value(s, options);
        }
    }
    return result;
}

// Copying bool (1B) instead of address
void print_flag(const std::string &name, const bool value)
{
    std::cout << "Flag option <" << name << "> is <" << (value ? "enabled" : "disabled") << ">" << std::endl;
}

void print_flags(const options_t &options)
{

    print_flag("x", options.flag_x);
    print_flag("y", options.flag_y);
    print_flag("grayscale", options.flag_gs);
    print_flag("t|transparent", options.flag_t);
}

void print_val(const std::string name, const bool enabled, const int &val)
{

    if (enabled)
        std::cout << "Value option <" << name << "> is <enabled> and associated with value <" << val << ">" << std::endl;
    else
        std::cout << "Value option <" << name << "> is <disabled>" << std::endl;
}

void print_val(const std::string name, const bool enabled, const float &val)
{
    if (enabled)
        std::cout << "Value option <" << name << "> is <enabled> and associated with value <" << val << ">" << std::endl;
    else
        std::cout << "Value option <" << name << "> is <disabled>" << std::endl;
}

void print_values(const options_t &options)
{
    print_val("r|red", options.flag_r, options.value_r);
    print_val("g|green", options.flag_g, options.value_g);
    print_val("b|blue", options.flag_b, options.value_b);
    print_val("a|alpha", options.flag_a, options.value_a);
}

void print_options(const options_t &options)
{
    print_flags(options);
    print_values(options);
    for (auto &&i : options.values)
    {
        std::cout << "Standalone value <" << i << ">" << std::endl;
    }
}
