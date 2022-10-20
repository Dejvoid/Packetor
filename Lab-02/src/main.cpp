#include "options.hpp"

int main(int argc, char **argv)
{
    args_t arguments(argv + 1, argv + argc);
    bool success = true;
    options_t options;
    success &= process_arguments(arguments, options);
    print_options(options);
    //return (success ? 0 : 1);
    return 0;
}