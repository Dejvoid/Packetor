#include "Regex.h"
#include "Parser.h"

Regex::Regex(const std::string& expr){
    root_ = Parser::parse_from_str(expr);
};

std::string Regex::print_ending(){

};

std::string Regex::print_starting(){

};

std::string Regex::print_neighbors(){

};

std::string Regex::print_epsilon(){

}

std::string Regex::print_info(){
    print_starting();
    print_neighbors();
    print_ending();
    print_epsilon();
};