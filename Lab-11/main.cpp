#include "Array.h"

int main(int argc, char **argv){
    std::cout << "HELLO" << std::endl;
    auto arr = Array<int>();
    std::cout << "DONE" << std::endl;
    arr.push_back(1);
    std::cout << "DONE1" << std::endl;
    int a = 2;
    std::cout << "DONE2" << std::endl;
    arr.push_back(a);
    std::cout << "DONE3" << std::endl;
    a = 3;
    arr.print();
    std::cout << "DONE4" << std::endl;
    std::cout << std::endl << arr << std::endl;
    std::cout << "DONE5" << std::endl;
    arr.pop_back();
    std::cout << "DONE6" << std::endl;
    std::cout << arr << std::endl;
    std::cout << "DONE7" << std::endl;
}