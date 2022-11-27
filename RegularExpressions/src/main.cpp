#include "Arguments.h"

#include <iostream>

int main(int argc, char **argv){
    args_t args(argv + 1, argv + argc);
    std::vector<std::string> expressions = expressions_from_args(args);
    for (auto it = expressions.begin(); it != expressions.end(); ++it){
        Regex reg(*it);
        reg.init_neighbor_method();
        std::cout << (*it) << std::endl;
        reg.print_info(std::cout);
    }
    return 0;
}