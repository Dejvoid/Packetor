#include "Arguments.h"

#include <iostream>

int main(int argc, char **argv){
    args_t args(argv + 1, argv + argc);
    std::vector<Regex> expressions = expressions_from_args(args);
    for (auto it = expressions.begin(); it != expressions.end(); ++it){
        // std::cout << *it << std::endl;
    }
    return 0;
}