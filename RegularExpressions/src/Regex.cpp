#include "Regex.h"
#include "Parser.h"

Regex::Regex(const std::string& expr){
    root_ = Parser::parse_from_str(expr);
};

void Regex::init_neighbor_method(){
    root_->add_neighbors(neighbors_);
};

void Regex::print_ending(std::ostream& os){
    os << "Ending: ";
    os << "{";
    for (auto it = ending_.begin(); it != ending_.end(); ++it){
        LiteralNode& literal = *it;
        if (it != ending_.begin())
            os << ", ";
        os << literal.value() << ":" << literal.index();
    }
    os << "}";
};

void Regex::print_starting(std::ostream& os){
    os << "Starting: ";
    os << "{";
    for (auto it = starting_.begin(); it != starting_.end(); ++it){
        LiteralNode& literal = *it;
        if (it != starting_.begin())
            os << ", ";
        os << literal.value() << ":" << literal.index();
    }
    os << "}";
};

void Regex::print_neighbors(std::ostream& os){
    os << "Neighbors: ";
    os << "{";
    
    os << "}";
};

void Regex::print_epsilon(std::ostream& os){
    os << "Epsilon: " << epsilon_ ? "true" : "false";
}

void Regex::print_info(std::ostream& os){
    print_starting(os);
    print_neighbors(os);
    print_ending(os);
    print_epsilon(os);
};