#include "options.hpp"

int main(int argc, char** argv){
    args_t arguments(argv + 1, argv + argc); 
    bool success = true;
    success &= process_arguments(arguments);
    //return (success ? 0 : 1);
    return 0;
}