#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv)
{
    std::ifstream ifs; // default ctor
    const char* path = "../data/data.txt";
    ifs.open(path);
    if (!ifs.good()){ // is filestream good?
        return 1;
    }
    std::string line;
    std::getline(ifs, line);
}