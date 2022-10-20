#ifndef OPTIONS_HPP_
#define OPTIONS_HPP_

#include <vector>
#include <string>

using args_t = std::vector<std::string>;

struct options_t {
    bool flag_x = false;
    bool flag_y = false;
    bool flag_gs = false;
    bool flag_t = false;
    bool flag_r = false;
    int value_r;
    bool flag_g = false;
    int value_g;
    bool flag_b = false;
    int value_b;
    bool flag_a = false;
    float value_a;
    std::vector<std::string> values; 
};

bool process_arguments(const args_t &args, options_t &options);

void print_options(const options_t &options);

#endif