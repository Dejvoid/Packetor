#include "Arguments.h"

#include <iostream>

int main(int argc, char **argv){
    args_t args(argv + 1, argv + argc);
    bool ret = true;
    std::vector<std::string> expressions;
    ret &= expressions_from_args(args, expressions);
    for (auto it = expressions.begin(); it != expressions.end(); ++it){
        Regex reg(*it);
        ret &= reg.init_neighbor_method();
        std::cout << (*it) << std::endl;
        reg.print_info(std::cout);
    }
    if (!ret)
        return 1;
    return 0;
}