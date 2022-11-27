#include "Regex.h"
#include "Parser.h"

Regex::Regex(const std::string& expr){
    root_ = Parser::parse_from_str(expr);
};

bool Regex::init_neighbor_method(){
    if (root_ == nullptr)
        return false;
    root_->add_starting(starting_);
    root_->add_neighbors(neighbors_);
    root_->add_ending(ending_);
    epsilon_ = root_->epsilon();
    return true;
};

void Regex::print_ending(std::ostream& os){
    os << "- Ending: ";
    os << "{";
    for (auto it = ending_.begin(); it != ending_.end(); ++it){
        LiteralNode* literal = *it;
        if (it != ending_.begin())
            os << ", ";
        os << literal->value() << ":" << literal->index();
    }
    os << "}" << std::endl;
};

void Regex::print_starting(std::ostream& os){
    os << "- Starting: ";
    os << "{";
    for (auto it = starting_.begin(); it != starting_.end(); ++it){
        LiteralNode* literal = *it;
        if (it != starting_.begin())
            os << ", ";
        os << literal->value() << ":" << literal->index();
    }
    os << "}" << std::endl;
};

void Regex::print_neighbors(std::ostream& os){
    os << "- Neighbors: ";
    os << "{";
    for (auto it = neighbors_.begin(); it != neighbors_.end(); ++it){
        auto pair = *it;
        if (it != neighbors_.begin())
            os << ", ";
        os << "(" << pair->left->value() << ":" << pair->left->index() << ", " << pair->right->value() << ":" << pair->right->index() << ")";
    }
    os << "}" << std::endl;
};

void Regex::print_epsilon(std::ostream& os){
    os << "- Epsilon: ";
    
    if (epsilon_)
        os << "true";
    else
        os <<"false";
    os  << std::endl;
}

void Regex::print_info(std::ostream& os){
    print_starting(os);
    print_neighbors(os);
    print_ending(os);
    print_epsilon(os);
    os << std::endl;
};