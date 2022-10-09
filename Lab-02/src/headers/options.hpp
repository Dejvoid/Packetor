#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <vector>
#include <string>

using args_t = std::vector<std::string>;

bool process_value_option(const std::string& name);

bool process_flag_option(const std::string& name);

bool process_arguments(const args_t& args);

#endif