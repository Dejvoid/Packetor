#ifndef ARGS_HPP_
#define ARGS_HPP_

#include <string>
#include <vector>

using args_t = std::vector<std::string>;


struct options_t {
    bool list_interfaces = false;
    bool out_to_file = false;
    std::string output_file;
};

#endif