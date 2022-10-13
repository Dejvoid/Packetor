#ifndef OPTIONS_HPP_
#define OPTIONS_HPP_

#include <vector>
#include <string>

using args_t = std::vector<std::string>;

bool process_value_option(const std::string& name, const std::string& value);

bool process_flag_option(const std::string& name);

bool process_standalone_value(const std::string& value);

bool process_arguments(const args_t& args);

#endif